// test-pplist-replace.c - тестирование функции replace итераторов обобщенного списка ppList
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
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  ppListIterator_VAR(int, it);
  int res;

  // Тесты для ppListIterator_replace
  printf("REPLACE\n\n");

  // 1. Замена первого элемента (головы)
  printf("Test 1: Replace head element (10 -> 99)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr1[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr1);
  int expected1[] = {99,20,30};
  ppList_FILL_FROM_ARRAY(anw, expected1);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_REPLACE(it, 99);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 2. Замена хвоста
  printf("Test 2: Replace tail element (30 -> 77)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr2);
  int expected2[] = {10,20,77};
  ppList_FILL_FROM_ARRAY(anw, expected2);
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_REPLACE(it, 77);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3. Замена элемента в середине
  printf("Test 3: Replace middle element (20 -> 55)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {10,55,30,40};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_NEXT(it);
  ppListIterator_REPLACE(it, 55);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 4. Замена в списке из одного элемента
  printf("Test 4: Replace single element (42 -> 100)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 42);
  int expected4[] = {100};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_REPLACE(it, 100);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 5. Замена с итератором, указывающим на NULL
  printf("Test 5: Replace with iterator pointing to NULL\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr5);
  ppList_FILL_FROM_ARRAY(anw, arr5);
  it.list = (ppList*)&l;
  it.node = NULL;
  print_list((ppList*)&l, "l");
  res = ppListIterator_replace((ppListIterator*)&it);
  check_condition(res == 0, "return value = 0 (no replacement)", &errors);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}