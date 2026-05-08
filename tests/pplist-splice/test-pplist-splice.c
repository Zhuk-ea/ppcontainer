// test-pplist-splice.c - объединённые тесты для splice_after и splice_before
#include <stdio.h>
#include "pplist.h"

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

void print_2_lists(ppList* l1, ppList* l2) {
  printf("l1: ");
  ppList_print2(stdout, l1);
  printf("l2: ");
  ppList_print2(stdout, l2);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l1);
  ppList_VAR(int, l2);
  ppList_VAR(int, anw);
  ppList_VAR(int, anw2);

  ppListIterator_VAR(int, src_begin);
  ppListIterator_VAR(int, src_end);
  ppListIterator_VAR(int, pos);

  int arr1[] = {1, 2, 4, 5, 6, 7, 8};
  int arr2[] = {1, 3, 6, 9, 10, 11};
  int pos_val, begin_val, end_val;

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  print_2_lists((ppList*)&l1, (ppList*)&l2);
  printf("\n-------------------------------------------\n\n");

  // 1. Тесты для ppList_splice_after
  printf("SPLICE_AFTER\n\n");

  // Тест 1.1: вставка src после головы
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw1[] = {1,1,3,6,9,10,11,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw1);
  ppList_CLEAR(anw2);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 1.1: Splice after head\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.2: вставка src после элемента в середине
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw2[] = {1,2,4,1,3,6,9,10,11,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw2);
  ppList_CLEAR(anw2);

  ppList_BEGIN(l1, pos); ppListIterator_NEXT(pos); ppListIterator_NEXT(pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 1.2: Splice after element in middle\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.3: вставка src после хвоста
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw3[] = {1,2,4,5,6,7,8,1,3,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw, arr_anw3);
  ppList_CLEAR(anw2);

  ppList_END(l1, pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 1.3: Splice after tail\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.4: вставка после NULL (в начало списка)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw4[] = {1,3,6,9,10,11,1,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw4);
  ppList_CLEAR(anw2);

  ppList_END(l1, pos); ppListIterator_NEXT(pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 1.4: Splice after NULL (insert before head)\n");
  printf("Dest position: after NULL (before head)\n");
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.5: вставка диапазона из одного элемента после головы
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw5[] = {1,3,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw5);
  int arr_anw2_5[] = {1,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw2, arr_anw2_5);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l2, src_end);
  for (int i = 0; i < 2; ++i) ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 1.5: Splice single element after head\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.6: перемещение диапазона [2,5) после элемента 7 (внутри одного списка)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw6[] = {1,5,6,7,2,4,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw6);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, pos);
  for (int i = 0; i < 5; ++i) ppListIterator_NEXT(pos);
  ppList_BEGIN(l1, src_begin); ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l1, src_end);
  for (int i = 0; i < 3; ++i) ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 1.6: Splicing within one list without overlapping\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 1.7: вставка пустого src-диапазона
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr1);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin);
  src_end = src_begin;
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 1.7: Splice empty src (should do nothing)\n");
  printf("Dest position: after %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_AFTER(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для ppList_splice_before
  printf("SPLICE_BEFORE\n\n");

  // Тест 2.1: вставка src перед головой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b1[] = {1,3,6,9,10,11,1,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b1);
  ppList_CLEAR(anw2);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 2.1: Splice before head\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.2: вставка src перед элементом в середине (перед 4)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b2[] = {1,2,1,3,6,9,10,11,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b2);
  ppList_CLEAR(anw2);

  ppList_BEGIN(l1, pos); ppListIterator_NEXT(pos); ppListIterator_NEXT(pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 2.2: Splice before element in middle\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.3: вставка src перед хвостом (перед 8)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b3[] = {1,2,4,5,6,7,1,3,6,9,10,11,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b3);
  ppList_CLEAR(anw2);

  ppList_END(l1, pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 2.3: Splice before tail\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.4: вставка перед NULL (в конец списка)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b4[] = {1,2,4,5,6,7,8,1,3,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b4);
  ppList_CLEAR(anw2);

  ppList_END(l1, pos); ppListIterator_NEXT(pos);
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 2.4: Splice before NULL (insert after tail)\n");
  printf("Dest position: before NULL (after tail)\n");
  printf("Src range: [%d, NULL)\n", begin_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.5: вставка диапазона из одного элемента перед головой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b5[] = {3,1,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b5);
  int arr_anw2_b5[] = {1,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw2, arr_anw2_b5);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l2, src_end);
  for (int i = 0; i < 2; ++i) ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 2.5: Splice single element before head\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.6: перемещение диапазона [2,5) перед элементом 7
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw_b6[] = {1,5,6,2,4,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw_b6);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, pos);
  for (int i = 0; i < 5; ++i) ppListIterator_NEXT(pos);
  ppList_BEGIN(l1, src_begin); ppListIterator_NEXT(src_begin);
  ppList_BEGIN(l1, src_end);
  for (int i = 0; i < 3; ++i) ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 2.6: Splicing within one list without overlapping\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n");

  // Тест 2.7: вставка пустого src-диапазона
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr1);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, pos);
  ppList_BEGIN(l2, src_begin);
  src_end = src_begin;
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 2.7: Splice empty src (should do nothing)\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);
  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  check_list((ppList*)&l1, (ppList*)&anw, "l1", &errors);
  check_list((ppList*)&l2, (ppList*)&anw2, "l2", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}