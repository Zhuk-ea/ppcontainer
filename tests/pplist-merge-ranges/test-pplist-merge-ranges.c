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
  printf("\n-------------------------------------------\n\n");
  
  // -------------------------------------------
  // Тест 1: пустой dest в хвосте, src - весь список l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw1[] = {1,2,4,5,6,7,8,1,3,6,9,10,11};
  for (int i = 0; i < 13; ++i) {
    ppList_PUSH_BACK(anw, anw1[i]);
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_END(l1, dest_begin); ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;

  ppList_BEGIN(l2, src_begin); ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(val1, src_begin);
 
  printf("Merge empty dest range at tail, src entire list:\n");
  printf("Dest range: [NULL, NULL)\n");
  printf("Src range: [%d, NULL)\n", val1);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 2: пустой dest в середине, src - весь список l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw2[] = {1,1,3,6,9,10,11,2,4,5,6,7,8};
  for (int i = 0; i < 13; ++i) {
    ppList_PUSH_BACK(anw, anw2[i]);
  }
  print_2_lists((ppList*)&l1, (ppList*)&l2);

  ppList_BEGIN(l1, dest_begin); ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);

  printf("Merge empty dest range in middle, src entire list:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 3: непустые диапазоны, без головы/хвоста
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw3[] = {1,2,3,4,5,6,6,9,7,8};
  for (int i = 0; i < 10; ++i) {
    ppList_PUSH_BACK(anw, anw3[i]);
  }
  print_2_lists((ppList*)&l1, (ppList*)&l2);

  ppList_BEGIN(l1, dest_begin); ppListIterator_NEXT(dest_begin);
  ppList_BEGIN(l1, dest_end);
  for (int i = 0; i < 5; ++i) {
    ppListIterator_NEXT(dest_end);
  }
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l2, src_end);
  for (int i = 0; i < 4; ++i) {
    ppListIterator_NEXT(src_end);
  }

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  ppListIterator_GET_VAL(val4, src_end);

  printf("Merge non-empty ranges, no head/tail involvement:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val4);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 4: пустой dest-диапазон в голове, src - весь список l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw4[] = {1,3,6,9,10,11,1,2,4,5,6,7,8};
  for (int i = 0; i < 13; ++i) {
    ppList_PUSH_BACK(anw, anw4[i]);
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_BEGIN(l1, dest_begin);
  dest_end = dest_begin;

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);

  printf("Merge empty dest range at head, src entire list:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 5: dest-диапазон включает голову, src от середины до конца
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw5[] = {1,2,3,4,5,6,9,10,11,6,7,8};
  for (int i = 0; i < 12; ++i) {
    ppList_PUSH_BACK(anw, anw5[i]);
  }

  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_BEGIN(l1, dest_begin);
  ppList_BEGIN(l1, dest_end);
  for (int i = 0; i < 4; ++i) {
    ppListIterator_NEXT(dest_end);
  }
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);

  printf("Merge dest range includes head, src range from middle to end:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 6: dest-диапазон включает хвост, src весь список
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  int anw6[] = {1,2,4,5,6,1,3,6,7,8,9,10,11};
  for (int i = 0; i < 13; ++i) {
    ppList_PUSH_BACK(anw, anw6[i]);
  }
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_BEGIN(l1, dest_begin);
  for (int i = 0; i < 5; ++i) {
    ppListIterator_NEXT(dest_begin);
  }
  ppList_END(l1, dest_end); ppListIterator_NEXT(dest_end);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, src_begin);

  printf("Merge dest range includes tail, src entire list:\n");
  printf("Dest range: [%d, NULL)\n", val1);
  printf("Src range: [%d, NULL)\n", val2);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 7: пустые диапазоны (оба пустые)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
    ppList_PUSH_BACK(anw, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_BEGIN(l1, dest_begin); ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin); ppListIterator_NEXT(src_begin);
  src_end = src_begin;

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  ppListIterator_GET_VAL(val4, src_end);

  printf("Merge empty ranges:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val4);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  // -------------------------------------------
  // Тест 8: src-диапазон пустой (ничего не делается)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw);
  for (int i = 0; i < 7; ++i) {
    ppList_PUSH_BACK(l1, arr1[i]);
    ppList_PUSH_BACK(anw, arr1[i]);
  }
  for (int i = 0; i < 6; ++i) {
    ppList_PUSH_BACK(l2, arr2[i]);
  }
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  ppList_BEGIN(l1, dest_begin); ppListIterator_NEXT(dest_begin);
  ppList_END(l1, dest_end); ppListIterator_PREV(dest_end);
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin);
  src_end = src_begin;

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);

  printf("Merge dest non-empty, src empty range:\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  is_correct((ppList*)&l1, (ppList*)&anw);

  printf("l1: ");
  ppList_print2(stdout, (ppList*)&l1);
  printf("\n-------------------------------------------\n\n");

  return 0;
}