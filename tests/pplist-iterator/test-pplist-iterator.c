// test-pplist-iterator.c - тестирование функций итераторов
#include <stdio.h>
#include "pplist.h"
#include "test-pplist-common.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>;
ppListIterator+<int;>;

//------------------------------------------------------------------------------
// Обработчик вывода
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}


//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  ppList_VAR(int, l);
  ppListIterator_VAR(int, it);
  int val;

  printf("\n-------------------------------------------\n\n");

  // 1. Тесты для ppList_begin
  printf("BEGIN\n\n");

  // 1.1 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 99);
  printf("Test 1.1: begin on single-element list\n");
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 99, "begin points to 99", &errors);
  printf("\n");

  // 1.2 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr1[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr1);
  printf("Test 1.2: begin on multi-element list\n");
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 10, "begin points to first element (10)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для ppList_end
  printf("END\n\n");

  // 2.1 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 55);
  printf("Test 2.1: end on single-element list\n");
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 55, "end points to 55 (last element)", &errors);
  printf("\n");

  // 2.2 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr2[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(l, arr2);
  printf("Test 2.2: end on multi-element list\n");
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 5, "end points to last element (5)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 3. Тесты для ppList_current_iterator
  printf("CURRENT_ITERATOR\n\n");

  // 3.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 3.1: current_iterator on empty list\n");
  ppList_current_iterator((ppList*)&l, (ppListIterator*)&it);
  check_condition(it.node == NULL, "node is NULL", &errors);
  printf("\n");

  // 3.2 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 77);
  printf("Test 3.2: current_iterator on single element\n");
  print_list((ppList*)&l, "l");
  ppList_current_iterator((ppList*)&l, (ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 77, "current_iterator points to 77 (tail)", &errors);
  printf("\n");

  // 3.3 Список из нескольких элементов, current перемещён вручную
  ppList_CLEAR(l);
  int arr3[] = {100,200,300};
  ppList_FILL_FROM_ARRAY(l, arr3);
  printf("Test 3.3: current_iterator after moving current to head\n");
  print_list((ppList*)&l, "l");
  ppList_front_current((ppList*)&l);
  ppList_current_iterator((ppList*)&l, (ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 100, "current_iterator points to head (100)", &errors);
  printf("\n");

  printf("Test 3.4: current_iterator after moving current to tail\n");
  ppList_back_current((ppList*)&l);
  ppList_current_iterator((ppList*)&l, (ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 300, "current_iterator points to tail (300)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 4. Тесты для ppListIterator_next
  printf("NEXT\n\n");

  // 4.1 Итератор с NULL
  ppList_CLEAR(l);
  it.list = (ppList*)&l;
  it.node = NULL;
  printf("Test 4.1: next on NULL iterator\n");
  int res = ppListIterator_next((ppListIterator*)&it);
  check_condition(res == 0 && it.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 4.2 Список из одного элемента: next переводит на NULL, возвращает 1
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 42);
  ppList_BEGIN(l, it);
  printf("Test 4.2: next on single-element list\n");
  print_list((ppList*)&l, "l");
  res = ppListIterator_next((ppListIterator*)&it);
  check_condition(res == 1 && it.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 4.3 Список из нескольких элементов: next до NULL и затем next возвращает 0
  ppList_CLEAR(l);
  int arr4[] = {5,6,7,8};
  ppList_FILL_FROM_ARRAY(l, arr4);
  ppList_BEGIN(l, it);   // it на 5
  printf("Test 4.3: next through list to NULL\n");
  print_list((ppList*)&l, "l");
  res = ppListIterator_next((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 6, "first next -> 6, returns 1", &errors);
  res = ppListIterator_next((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 7, "second next -> 7, returns 1", &errors);
  res = ppListIterator_next((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 8, "third next -> 8, returns 1", &errors);
  res = ppListIterator_next((ppListIterator*)&it);
  check_condition(res == 1 && it.node == NULL, "fourth next -> 1, node becomes NULL", &errors);
  res = ppListIterator_next((ppListIterator*)&it);
  check_condition(res == 0 && it.node == NULL, "fifth next -> 0, stays NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  // 5. Тесты для ppListIterator_prev
  printf("PREV\n\n");

  // 5.1 Итератор с NULL
  it.list = (ppList*)&l;
  it.node = NULL;
  printf("Test 5.1: prev on NULL iterator\n");
  res = ppListIterator_prev((ppListIterator*)&it);
  check_condition(res == 0 && it.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 5.2 Список из одного элемента: prev переводит на NULL, возвращает 1
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 99);
  ppList_BEGIN(l, it);
  printf("Test 5.2: prev on single-element list\n");
  print_list((ppList*)&l, "l");
  res = ppListIterator_prev((ppListIterator*)&it);
  check_condition(res == 1 && it.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 5.3 Список из нескольких элементов: prev до NULL и затем prev возвращает 0
  ppList_CLEAR(l);
  ppList_FILL_FROM_ARRAY(l, arr4);
  ppList_END(l, it);
  printf("Test 5.3: prev through list to NULL\n");
  print_list((ppList*)&l, "l");
  res = ppListIterator_prev((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 7, "first prev -> 7, returns 1", &errors);
  res = ppListIterator_prev((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 6, "second prev -> 6, returns 1", &errors);
  res = ppListIterator_prev((ppListIterator*)&it);
  ppListIterator_GET_VAL(val, it);
  check_condition(res == 1 && val == 5, "third prev -> 5, returns 1", &errors);
  res = ppListIterator_prev((ppListIterator*)&it);
  check_condition(res == 1 && it.node == NULL, "fourth prev -> 1, node becomes NULL", &errors);
  res = ppListIterator_prev((ppListIterator*)&it);
  check_condition(res == 0 && it.node == NULL, "fifth prev -> 0, stays NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  // 6. Тесты для ppListIterator_get_value
  printf("GET_VALUE\n\n");

  // 6.1 Получение значений на разных позициях (итератор не NULL)
  ppList_CLEAR(l);
  int arr5[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr5);
  printf("Test 6.1: get_value on begin, middle, end\n");
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  int v1, v2, v3;
  ppListIterator_GET_VAL(v1, it);
  ppListIterator_NEXT(it);
  ppListIterator_NEXT(it);
  ppListIterator_GET_VAL(v2, it);
  ppListIterator_NEXT(it);
  ppListIterator_GET_VAL(v3, it);
  check_condition(v1 == 1 && v2 == 3 && v3 == 4, "get_value returns 1,3,4 correctly", &errors);
  printf("\n");

  // 6.2 Проверка, что get_value не меняет итератор
  printf("Test 6.2: get_value does not move iterator\n");
  ppList_BEGIN(l, it);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 1, "first get_value -> 1", &errors);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 1, "second get_value still -> 1 (iterator unchanged)", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}