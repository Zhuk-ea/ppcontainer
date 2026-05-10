// test-pplist-pop.c - тестирование функций семейства pop для списка
#include <stdio.h>
#include "pplist.h"
#include "test-pplist-common.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>;
ppListIterator+<int;>;

//------------------------------------------------------------------------------
// Обработчик специализации, обеспечивающий вывод целочисленного элемента
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}


//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  int cur_val;

  // 1. Тесты для ppList_pop_back
  printf("POP_BACK\n\n");

  // 1.1 Пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test 1.1: pop_back on empty list (should do nothing)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_pop_back((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 1.2 Список из одного элемента
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 5);
  printf("Test 1.2: pop_back on single element list\n");
  print_list((ppList*)&l, "l");
  ppList_pop_back((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 1.3 Список из нескольких элементов
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr1[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr1);
  int expected1[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(anw, expected1);
  printf("Test 1.3: pop_back on [10,20,30,40]\n");
  print_list((ppList*)&l, "l");
  ppList_back_current((ppList*)&l);
  ppList_pop_back((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для ppList_pop_front
  printf("POP_FRONT\n\n");

  // 2.1 Пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test 2.1: pop_front on empty list\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_pop_front((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 2.2 Список из одного элемента
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 7);
  printf("Test 2.2: pop_front on single element\n");
  print_list((ppList*)&l, "l");
  ppList_pop_front((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 2.3 Список из нескольких элементов
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {100,200,300};
  ppList_FILL_FROM_ARRAY(l, arr2);
  int expected2[] = {200,300};
  ppList_FILL_FROM_ARRAY(anw, expected2);
  printf("Test 2.3: pop_front on [100,200,300]\n");
  print_list((ppList*)&l, "l");
  ppList_pop_front((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  // 3. Тесты для ppList_pop_current
  printf("POP_CURRENT\n\n");

  // 3.1 Удаление головы (эквивалент pop_front)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {2,3};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  printf("Test 3.1: pop_current on head (1)\n");
  print_list((ppList*)&l, "l");
  ppList_front_current((ppList*)&l);
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3.2 Удаление хвоста (эквивалент pop_back)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3b[] = {1,2};
  ppList_FILL_FROM_ARRAY(anw, expected3b);
  printf("Test 3.2: pop_current on tail (3)\n");
  print_list((ppList*)&l, "l");
  ppList_back_current((ppList*)&l);
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3.3 Удаление среднего элемента
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr4);
  int expected4[] = {1,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  printf("Test 3.3: pop_current on middle element (2)\n");
  print_list((ppList*)&l, "l");
  l.current = l.head->next;
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3.4 Удаление из списка из двух элементов (удаляем голову)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {9,10};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {10};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  printf("Test 3.4: pop_current on head of two-element list\n");
  print_list((ppList*)&l, "l");
  ppList_front_current((ppList*)&l);
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3.5 Удаление из списка из двух элементов (удаляем хвост)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5b[] = {9};
  ppList_FILL_FROM_ARRAY(anw, expected5b);
  printf("Test 3.5: pop_current on tail of two-element list\n");
  print_list((ppList*)&l, "l");
  ppList_back_current((ppList*)&l);
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3.6 Попытка удалить current == NULL (пустой список) – функция не должна падать
  ppList_CLEAR(l);
  ppList_CLEAR(anw);
  printf("Test 3.6: pop_current on empty list (current NULL)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_pop_current((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}