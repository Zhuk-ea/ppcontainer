// test-pp-list-riterator.c - тестирование базовых функций обратных итераторов обобщенного списка ppList
#include <stdio.h>
#include "pplist.h"
#include "test-pplist-common.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>;
ppListRIterator+<int;>;

//------------------------------------------------------------------------------
// Обработчик вывода
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  ppList_VAR(int, l);
  ppListRIterator_VAR(int, rit);
  int val;

  printf("\n-------------------------------------------\n\n");

  // 1. Тесты для ppList_rbegin
  printf("RBEGIN\n\n");

  // 1.1 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 99);
  printf("Test 1.1: rbegin on single-element list\n");
  print_list((ppList*)&l, "l");
  ppList_RBEGIN(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 99, "rbegin points to 99 (tail)", &errors);
  printf("\n");

  // 1.2 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr1[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr1);
  printf("Test 1.2: rbegin on multi-element list\n");
  print_list((ppList*)&l, "l");
  ppList_RBEGIN(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 40, "rbegin points to last element (40)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для ppList_rend
  printf("REND\n\n");

  // 2.1 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 55);
  printf("Test 2.1: rend on single-element list\n");
  print_list((ppList*)&l, "l");
  ppList_REND(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 55, "rend points to 55 (head)", &errors);
  printf("\n");

  // 2.2 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr2[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(l, arr2);
  printf("Test 2.2: rend on multi-element list\n");
  print_list((ppList*)&l, "l");
  ppList_REND(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 1, "rend points to first element (1)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 3. Тесты для ppList_current_riterator
  printf("CURRENT_RITERATOR\n\n");

  // 3.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 3.1: current_riterator on empty list\n");
  ppList_CURRENT_RITERATOR(l, rit);
  check_condition(rit.node == NULL, "node is NULL", &errors);
  printf("\n");

  // 3.2 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 77);
  printf("Test 3.2: current_riterator on single element\n");
  print_list((ppList*)&l, "l");
  ppList_CURRENT_RITERATOR(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 77, "current_riterator points to 77 (tail)", &errors);
  printf("\n");

  // 3.3 Список из нескольких элементов, current перемещён вручную
  ppList_CLEAR(l);
  int arr3[] = {100,200,300};
  ppList_FILL_FROM_ARRAY(l, arr3);
  printf("Test 3.3: current_riterator after moving current to head\n");
  print_list((ppList*)&l, "l");
  ppList_front_current((ppList*)&l);   // current = 100
  ppList_CURRENT_RITERATOR(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 100, "current_riterator points to head (100)", &errors);
  printf("\n");

  printf("Test 3.4: current_riterator after moving current to tail\n");
  ppList_back_current((ppList*)&l);    // current = 300
  ppList_CURRENT_RITERATOR(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 300, "current_riterator points to tail (300)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 4. Тесты для ppListRIterator_next
  printf("NEXT\n\n");

  // 4.1 Итератор с NULL
  ppList_CLEAR(l);
  rit.list = (ppList*)&l;
  rit.node = NULL;
  printf("Test 4.1: next on NULL iterator\n");
  int res = ppListRIterator_next((ppListRIterator*)&rit);
  check_condition(res == 0 && rit.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 4.2 Список из одного элемента: next переводит на NULL
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 42);
  ppList_RBEGIN(l, rit);
  printf("Test 4.2: next on single-element list\n");
  print_list((ppList*)&l, "l");
  res = ppListRIterator_next((ppListRIterator*)&rit);
  check_condition(res == 1 && rit.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 4.3 Список из нескольких элементов: next шагает к голове
  ppList_CLEAR(l);
  int arr4[] = {5,6,7,8};
  ppList_FILL_FROM_ARRAY(l, arr4);
  ppList_RBEGIN(l, rit);
  printf("Test 4.3: next through list to head and then NULL\n");
  print_list((ppList*)&l, "l");
  res = ppListRIterator_next((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 7, "first next -> 7, returns 1", &errors);
  res = ppListRIterator_next((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 6, "second next -> 6, returns 1", &errors);
  res = ppListRIterator_next((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 5, "third next -> 5, returns 1", &errors);
  res = ppListRIterator_next((ppListRIterator*)&rit);
  check_condition(res == 1 && rit.node == NULL, "fourth next -> 1, node becomes NULL", &errors);
  res = ppListRIterator_next((ppListRIterator*)&rit);
  check_condition(res == 0 && rit.node == NULL, "fifth next -> 0, stays NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  // 5. Тесты для ppListRIterator_prev
  printf("PREV\n\n");

  // 5.1 Итератор с NULL
  rit.list = (ppList*)&l;
  rit.node = NULL;
  printf("Test 5.1: prev on NULL iterator\n");
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  check_condition(res == 0 && rit.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 5.2 Список из одного элемента: prev переводит на NULL
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 99);
  ppList_RBEGIN(l, rit);
  printf("Test 5.2: prev on single-element list\n");
  print_list((ppList*)&l, "l");
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  check_condition(res == 1 && rit.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 5.3 Список из нескольких элементов: prev шагает от головы к хвосту
  ppList_CLEAR(l);
  ppList_FILL_FROM_ARRAY(l, arr4);
  ppList_REND(l, rit);
  printf("Test 5.3: prev through list to tail and then NULL\n");
  print_list((ppList*)&l, "l");
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 6, "first prev -> 6, returns 1", &errors);
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 7, "second prev -> 7, returns 1", &errors);
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(res == 1 && val == 8, "third prev -> 8, returns 1", &errors);
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  check_condition(res == 1 && rit.node == NULL, "fourth prev -> 1, node becomes NULL", &errors);
  res = ppListRIterator_prev((ppListRIterator*)&rit);
  check_condition(res == 0 && rit.node == NULL, "fifth prev -> 0, stays NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  // 6. Тесты для ppListRIterator_get_value
  printf("GET_VALUE\n\n");

  // 6.1 Получение значений на разных позициях
  ppList_CLEAR(l);
  int arr5[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr5);
  printf("Test 6.1: get_value on rbegin (4), after next (3), after next (2)\n");
  print_list((ppList*)&l, "l");
  ppList_RBEGIN(l, rit);
  int v1, v2, v3;
  ppListRIterator_GET_VAL(v1, rit);
  ppListRIterator_NEXT(rit);
  ppListRIterator_GET_VAL(v2, rit);
  ppListRIterator_NEXT(rit);
  ppListRIterator_GET_VAL(v3, rit);
  check_condition(v1 == 4 && v2 == 3 && v3 == 2, "get_value returns 4,3,2 correctly", &errors);
  printf("\n");

  // 6.2 Проверка, что get_value не меняет итератор
  printf("Test 6.2: get_value does not move iterator\n");
  ppList_RBEGIN(l, rit);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 4, "first get_value -> 4", &errors);
  ppListRIterator_GET_VAL(val, rit);
  check_condition(val == 4, "second get_value still -> 4 (iterator unchanged)", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}