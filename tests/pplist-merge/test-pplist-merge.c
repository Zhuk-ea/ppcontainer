// test-pp-list-merge.c - тестирование функции merge для списка
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


int cmp_int(char* a, char* b) {
  int x, y;
  memcpy(&x, a, sizeof(int));
  memcpy(&y, b, sizeof(int));
  return (x < y);
}

void is_correct(ppList* l, ppList* anw) {
  if (ppList_is_equal(l, anw, sizeof(int))) printf("Correct\n");
  else printf("Incorrect\n");

}

void print_2_lists(ppList* l1, ppList* l2) {
  printf("l1: ");
  ppList_print2(stdout, l1);

  printf("l2: ");
  ppList_print2(stdout, l2);
}


//------------------------------------------------------------------------------
int main(void) {

  ppList_VAR(int, l1);
  ppList_VAR(int, l2);
  ppList_VAR(int, anw);


  printf("\n-------------------------------------------\n\n");
  print_2_lists((ppList*)&l1, (ppList*)&l2);

  printf("Merge empty lists: ");

  ppList_MERGE(l1, l2, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);


  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);


  printf("\n-------------------------------------------\n\n");

  ppList_PUSH_BACK(l1, 1);
  ppList_PUSH_BACK(l1, 3);


  ppList_PUSH_BACK(anw, 1);
  ppList_PUSH_BACK(anw, 3);
  

  print_2_lists((ppList*)&l1, (ppList*)&l2);


  printf("Merge not empty with empty: ");

  ppList_MERGE(l1, l2, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);


  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);

  printf("\n-------------------------------------------\n\n");

  ppList_clear((ppList*)&l1);
  ppList_clear((ppList*)&anw);

  ppList_PUSH_BACK(l2, 1);
  ppList_PUSH_BACK(l2, 3);


  ppList_PUSH_BACK(anw, 1);
  ppList_PUSH_BACK(anw, 3);

  print_2_lists((ppList*)&l1, (ppList*)&l2);

  printf("Merge empty with not empty: ");

  ppList_MERGE(l1, l2, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);


  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);


  printf("\n-------------------------------------------\n\n");
  ppList_clear((ppList*)&l1);
  ppList_clear((ppList*)&anw);


  int arr1[] = {1, 2, 4, 5};
  for (int i = 0; i < 4; ++i) {
    ppList_PUSH_BACK(l1, arr1[i])
  }

  int arr2[] = {1, 3, 6, 9, 10};
  for (int i = 0; i < 5; ++i) {
    ppList_PUSH_BACK(l2, arr2[i])
  }

  int aanw[] = {1, 1, 2, 3, 4, 5, 6, 9, 10};
  for (int i = 0; i < 9; ++i) {
    ppList_PUSH_BACK(anw, aanw[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);

  printf("Merge sorted lists: ");

  ppList_MERGE(l1, l2, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);



  printf("\n-------------------------------------------\n\n");

  ppList_clear((ppList*)&l1);
  ppList_clear((ppList*)&anw);

  int arr3[] = {2, 4};
  for (int i = 0; i < 2; ++i) {
    ppList_PUSH_BACK(l1, arr3[i])
  }

  int arr4[] = {1, 3};
  for (int i = 0; i < 2; ++i) {
    ppList_PUSH_BACK(l2, arr4[i])
  }

  int aanw2[] = {1, 2, 3, 4};
  for (int i = 0; i < 4; ++i) {
    ppList_PUSH_BACK(anw, aanw2[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);

  printf("Merge sorted lists with replacing head: ");

  ppList_MERGE(l1, l2, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);


  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("anw: ");
  ppList_print2(stdout, (ppList*)&anw);


  printf("\n-------------------------------------------\n\n");


  ppList_clear((ppList*)&l1);
  ppList_clear((ppList*)&anw);

  int arr5[] = {5, 3};
  for (int i = 0; i < 2; ++i) {
    ppList_PUSH_BACK(l1, arr5[i])
  }

  int arr6[] = {2, 1};
  for (int i = 0; i < 2; ++i) {
    ppList_PUSH_BACK(l2, arr6[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);

  printf("Merge unsorted lists\n");

  ppList_MERGE(l1, l2, cmp_int);


  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");
  

  return 0;
} // end main