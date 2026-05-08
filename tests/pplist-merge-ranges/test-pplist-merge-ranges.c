// test-pplist-merge-ranges.c - тестирование функции merge-ranges для итераторов по списку
#include <stdio.h>
#include "pplist.h"

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
// Вспомогательные функции
void check_condition(int condition, const char* msg, int* errors) {
  if (condition) {
    printf("Correct | %s\n", msg);
  } else {
    printf("Incorrect | %s\n", msg);
    (*errors)++;
  }
}

void check_list(ppList* l, ppList* anw, const char* name, int* errors) {
  if (ppList_is_equal(l, anw, sizeof(int))) {
    printf("Correct | %s: ", name);
  } else {
    printf("Incorrect | %s: ", name);
    (*errors)++;
  }
  ppList_print2(stdout, l);
}

void print_list(ppList* l, const char* name) {
  printf("%s: ", name);
  ppList_print2(stdout, l);
}

int cmp_int(char* a, char* b) {
  int x, y;
  memcpy(&x, a, sizeof(int));
  memcpy(&y, b, sizeof(int));
  return (x < y);
}

int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l1);
  ppList_VAR(int, l2);
  ppList_VAR(int, anw);
  ppList_VAR(int, anw2);

  ppListIterator_VAR(int, dest_begin);
  ppListIterator_VAR(int, dest_end);
  ppListIterator_VAR(int, src_begin);
  ppListIterator_VAR(int, src_end);

  int arr1[] = {1,2,4,5,6,7,8};
  int arr2[] = {1,3,6,9,10,11};
  int val1, val2, val3, val4;

  // Тесты для ppList_merge_ranges
  printf("MERGE_RANGES\n\n");

  // Тест 1: пустой dest в хвосте, src - весь l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw1[] = {1,2,4,5,6,7,8,1,3,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw, arr_anw1);
  int empty[] = {};
  ppList_FILL_FROM_ARRAY(anw2, empty);

  ppList_END(l1, dest_begin);
  ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, src_begin);
  printf("Test 1: Merge empty dest range at tail, src entire list\n");
  printf("Dest range: [NULL, NULL)\n");
  printf("Src range: [%d, NULL)\n", val1);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2: пустой dest в середине, src - весь l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw2[] = {1,1,3,6,9,10,11,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw2);
  ppList_FILL_FROM_ARRAY(anw2, empty);

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  printf("Test 2: Merge empty dest range in middle, src entire list\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 3: непустые диапазоны, без головы/хвоста
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw3[] = {1,2,3,4,5,6,6,9,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw3);
  int arr_anw2_3[] = {1,10,11};
  ppList_FILL_FROM_ARRAY(anw2, arr_anw2_3);

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin);
  ppList_BEGIN(l1, dest_end);
  for (int i = 0; i < 5; ++i) ppListIterator_NEXT(dest_end);

  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l2, src_end);
  for (int i = 0; i < 4; ++i) ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  ppListIterator_GET_VAL(val4, src_end);
  printf("Test 3: Merge non-empty ranges, no head/tail involvement\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val4);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 4: пустой dest в голове, src - весь l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw4[] = {1,3,6,9,10,11,1,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw4);
  ppList_FILL_FROM_ARRAY(anw2, empty);

  ppList_BEGIN(l1, dest_begin);
  dest_end = dest_begin;

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  printf("Test 4: Merge empty dest range at head, src entire list\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 5: dest включает голову, src от середины до конца
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw5[] = {1,2,3,4,5,6,9,10,11,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw5);
  int arr_anw2_5[] = {1};
  ppList_FILL_FROM_ARRAY(anw2, arr_anw2_5);

  ppList_BEGIN(l1, dest_begin);
  ppList_BEGIN(l1, dest_end);
  for (int i = 0; i < 4; ++i) ppListIterator_NEXT(dest_end);

  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin);
  ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  printf("Test 5: Merge dest range includes head, src range from middle to end\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, NULL)\n", val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 6: dest включает хвост, src весь список l2
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw6[] = {1,2,4,5,6,1,3,6,7,8,9,10,11};
  ppList_FILL_FROM_ARRAY(anw, arr_anw6);
  ppList_FILL_FROM_ARRAY(anw2, empty);

  ppList_BEGIN(l1, dest_begin);
  for (int i = 0; i < 5; ++i) ppListIterator_NEXT(dest_begin);
  ppList_END(l1, dest_end);
  ppListIterator_NEXT(dest_end);

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end);
  ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, src_begin);
  printf("Test 6: Merge dest range includes tail, src entire list\n");
  printf("Dest range: [%d, NULL)\n", val1);
  printf("Src range: [%d, NULL)\n", val2);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 7: оба диапазона пустые (dest пуст, src пуст)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr1);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin);
  dest_end = dest_begin;
  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin);
  ppListIterator_NEXT(src_begin);
  src_end = src_begin;

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  ppListIterator_GET_VAL(val4, src_end);
  printf("Test 7: Merge both empty ranges\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val4);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 8: src пустой (ничего не делается)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr1);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, dest_begin);
  ppListIterator_NEXT(dest_begin);
  ppList_END(l1, dest_end);
  ppListIterator_PREV(dest_end);
  ppList_BEGIN(l2, src_begin);
  ppListIterator_NEXT(src_begin);
  src_end = src_begin;

  ppListIterator_GET_VAL(val1, dest_begin);
  ppListIterator_GET_VAL(val2, dest_end);
  ppListIterator_GET_VAL(val3, src_begin);
  printf("Test 8: Merge dest non-empty, src empty range\n");
  printf("Dest range: [%d, %d)\n", val1, val2);
  printf("Src range: [%d, %d)\n", val3, val3);

  ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_int);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}