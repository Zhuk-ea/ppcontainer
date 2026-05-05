// test-pplist-reverse.c - тестирование функции reverse для списка
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>; // Целочисленная специализация списка
ppListIterator+<int;>; // Целочисленная специализация итератора

//------------------------------------------------------------------------------
// Обработчик специализации, обеспечивающий вывод целочисленного элемента
// Выводится текущий элемент списка с предварительным переводом
// в область специализации
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}


void is_correct(ppList* l, ppList* anw) {
  if (ppList_is_equal(l, anw, sizeof(int))) printf("Correct ");
  else printf("Incorrect ");
}

void print_test_results(ppList* l, ppList* anw) {
    is_correct(l, anw);
    printf("| l: "); 
    ppList_print2(stdout, l);
}

//------------------------------------------------------------------------------
int main(void) {
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  ppList_VAR(int, empty);

  // --------------------------------------------------------------
  // Тест 1: пустой список

  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test 1: empty list\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&empty);
  printf("\n-------------------------------------------\n\n");

  // --------------------------------------------------------------
  // Тест 2: один элемент

  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {42};
  ppList_FILL_FROM_ARRAY(l, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr2);
  printf("Test 2: single element\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&anw);
  printf("\n-------------------------------------------\n\n");

  // --------------------------------------------------------------
  // Тест 3: два элемента

  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {1,2};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {2,1};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  printf("Test 3: two elements\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&anw);
  printf("\n-------------------------------------------\n\n");

  // --------------------------------------------------------------
  // Тест 4: три элемента (нечётное)

  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr4);
  int expected4[] = {3,2,1};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  printf("Test 4: three elements (odd)\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&anw);
  printf("\n-------------------------------------------\n\n");

  // --------------------------------------------------------------
  // Тест 5: четыре элемента (чётное)

  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {4,3,2,1};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  printf("Test 5: four elements (even)\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&anw);
  printf("\n-------------------------------------------\n\n");

  // --------------------------------------------------------------
  // Тест 6: разворот уже развёрнутого
  
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {5,6,7,8};
  ppList_FILL_FROM_ARRAY(l, arr6);
  ppList_FILL_FROM_ARRAY(anw, arr6);
  printf("Test 6: reverse twice (should restore original)\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  printf("\n");
  ppList_REVERSE(l);
  ppList_REVERSE(l);
  print_test_results((ppList*)&l, (ppList*)&anw);
  printf("\n-------------------------------------------\n\n");

  return 0;
}