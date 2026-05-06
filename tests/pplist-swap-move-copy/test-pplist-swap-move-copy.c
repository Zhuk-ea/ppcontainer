// test-pp-list-swap-move-copy.c - тестирование функций swap, move, copy обобщенного списка ppList
#include <stdio.h> 
#include "pplist.h"


ppList+<int;>; // Целочисленная специализация списка

//------------------------------------------------------------------------------
// Обработчик специализации, обеспечивающий вывод целочисленного элемента
// Выводится текущий элемент списка с предварительным переводом
// в область специализации
void ppList_element_print<ppList.int* l>(FILE* f) {
    fprintf(f, "%d ", l->@);
}
//------------------------------------------------------------------------------
// Вспомогательные функции проверки и вывода
void is_correct(ppList* l, ppList* anw) {
    if (ppList_is_equal(l, anw, sizeof(int))) printf("Correct");
    else printf("Incorrect");
}

void print_2_lists(ppList* l1, ppList* l2) {
    printf("l1: "); ppList_print2(stdout, l1);
    printf("l2: "); ppList_print2(stdout, l2);
}

void print_test_results(ppList* l1, ppList* l2, ppList* anw1, ppList* anw2) {
    printf("l1: ");
    is_correct(l1, anw1);
    printf(" | ");
    ppList_print2(stdout, l1);
    printf("l2: ");
    is_correct(l2, anw2);
    printf(" | ");
    ppList_print2(stdout, l2);
}

int main(void) {
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l1);
  ppList_VAR(int, l2);
  ppList_VAR(int, anw1);
  ppList_VAR(int, anw2);

  // 1. Тесты для ppList_swap
  printf("SWAP\n\n");

  // 1.1. swap двух пустых списков
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  printf("Test 1.1: swap two empty lists\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_swap((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n");


  // 1.2. swap пустого и непустого
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr1[] = {5,6,7};
  ppList_FILL_FROM_ARRAY(l2, arr1);
  ppList_FILL_FROM_ARRAY(anw1, arr1);  // после swap l1 получит arr1
  // anw2 остаётся пустым
  printf("Test 1.2: swap empty and non-empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_swap((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n");

  //1.3. swap двух непустых списков
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr2[] = {1,2,3};
  int arr3[] = {10,20};
  ppList_FILL_FROM_ARRAY(l1, arr2);
  ppList_FILL_FROM_ARRAY(l2, arr3);
  ppList_FILL_FROM_ARRAY(anw1, arr3);
  ppList_FILL_FROM_ARRAY(anw2, arr2);
  printf("Test 1.3: swap two non-empty lists\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_swap((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n-------------------------------------------\n\n");


  // 2. Тесты для ppList_move
  printf("MOVE\n\n");

  // 2.1 move из непустого в пустой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr4[] = {100,200};
  ppList_FILL_FROM_ARRAY(l2, arr4);
  ppList_FILL_FROM_ARRAY(anw1, arr4);

  printf("Test 2.1: move from non-empty to empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_move((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n");

  // 2.2. move из непустого в непустой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr5[] = {1,2};
  int arr6[] = {9,8,7};
  ppList_FILL_FROM_ARRAY(l1, arr5);
  ppList_FILL_FROM_ARRAY(l2, arr6);
  ppList_FILL_FROM_ARRAY(anw1, arr6);

  printf("Test 2.2: move from non-empty to non-empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_move((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n-------------------------------------------\n\n");

  // 3. Тесты для ppList_copy
  printf("COPY\n\n");

  // 3.1. copy из пустого в непустой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr7[] = {11,22};
  ppList_FILL_FROM_ARRAY(l1, arr7);
  ppList_CLEAR(anw1);
  ppList_CLEAR(anw2);
  printf("Test 3.1: copy from empty to non-empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_copy((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n");

  // 3.2 copy из непустого в пустой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr8[] = {100,200,300};
  ppList_FILL_FROM_ARRAY(l2, arr8);
  ppList_FILL_FROM_ARRAY(anw1, arr8);
  ppList_FILL_FROM_ARRAY(anw2, arr8);
  printf("Test 3.2: copy from non-empty to empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_copy((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n");

  // 3.3. copy из непустого в непустой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
  int arr9[] = {5,6};
  int arr10[] = {7,8,9};
  ppList_FILL_FROM_ARRAY(l1, arr9);
  ppList_FILL_FROM_ARRAY(l2, arr10);
  ppList_FILL_FROM_ARRAY(anw1, arr10);
  ppList_FILL_FROM_ARRAY(anw2, arr10);
  printf("Test 3.3: copy from non-empty to non-empty\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_copy((ppList*)&l1, (ppList*)&l2);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&anw2);
  printf("\n-------------------------------------------\n\n");

  return 0;
}