// test-pp-list-merge-ranges.c - тестирование функции merge-ranges для итераторов по списку
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

  ppListIterator_VAR(int, dest_begin);
  ppListIterator_VAR(int, src_begin);
  ppListIterator_VAR(int, dest_end);
  ppListIterator_VAR(int, src_end);

  int arr1[] = {1, 2, 4, 5, 6, 7, 8};
  int arr2[] = {1, 3, 6, 9, 10, 11};
  int val, val1, val2, val3, val4;

  // -------------------------------------------

  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i])
    ppList_PUSH_BACK(anw, arr1[i])
  }

  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);
  

  ppList_BEGIN(l1, dest_begin); ppListIterator_NEXT(dest_begin); 
  dest_end = dest_begin;


  ppList_BEGIN(l2, src_begin);ppListIterator_NEXT(src_begin); ppListIterator_NEXT(src_begin); 
  src_end = src_begin;

  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val4, src_end);
  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val3, src_begin);

  

  printf("Merge empty ranges: \n");
  printf("Dest range: [%i, %i)\nSrc range: [%i, %i)\n", val1, val2, val3, val4);
  
  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);

  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  
  printf("\n-------------------------------------------\n\n");
  

  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i])
    ppList_PUSH_BACK(anw, arr1[i])
  }

  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);
  

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin); 
  dest_end = dest_begin;


  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin); ppListIterator_NEXT(src_begin); 
  src_end = src_begin;

  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val4, src_end);
  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val3, src_begin);

  

  printf("Merge empty ranges: \n");
  printf("Dest range: [%i, %i)\nSrc range: [%i, %i)\n", val1, val2, val3, val4);
  
  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);

  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);


  printf("\n-------------------------------------------\n\n");

  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i])
  }

  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i])
  }

  int aanw[] = {1, 2, 3, 4, 5, 6, 9, 6, 7, 8};
  for (int i = 0; i < 10; ++i) {
    ppList_PUSH_BACK(anw, aanw[i])
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin); 
  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin); 

  ppList_END(l1, dest_end); ppListIterator_PREV(dest_end); ppListIterator_PREV(dest_end);
  ppList_END(l2, src_end); ppListIterator_PREV(src_end);

  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val4, src_end);
  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val3, src_begin);



  printf("Merge ranges, that do not have head or tail of lists in it: \n");
  printf("Dest range: [%i, %i)\nSrc range: [%i, %i)\n", val1, val2, val3, val4);


  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);



  printf("\n-------------------------------------------\n\n");

  return 0;
}