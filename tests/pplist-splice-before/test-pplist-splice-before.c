// test-pp-list-splice-before.c - тестирование функции splice_before для итераторов по списку
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

void print_2_lists(ppList* l1, ppList* l2) {
  printf("l1: ");
  ppList_print2(stdout, l1);

  printf("l2: ");
  ppList_print2(stdout, l2);
}

void print_test_results(ppList* l1, ppList* l2, ppList* anw1, ppList* anw2) {
  
  printf("l1: ");
  is_correct(l1, anw1);
  printf(" | ");
  ppList_print2(stdout,l1);
  printf("l2: ");
  is_correct(l2, anw2);
  printf(" | ");
  ppList_print2(stdout,l2);

}



int main(void) {

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
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int pos_val, begin_val, end_val;
  print_2_lists((ppList*)&l1, (ppList*)&l2);


  printf("\n-------------------------------------------\n\n");

  //Тест 1: вставка src перед головой
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);
  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw1[] = {1,3,6,9,10,11,1,2,4,5,6,7,8}; // вставка перед 1
  ppList_FILL_FROM_ARRAY(anw, arr_anw1);

  ppList_BEGIN(l1, pos);  // pos = 1

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);

  printf("Test 1: Splice before head\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n",begin_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);
  
  printf("\n-------------------------------------------\n\n");

  // Тест 2: вставка src перед элементом в середине (перед 4)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw2[] = {1,2,1,3,6,9,10,11,4,5,6,7,8}; // вставка перед 4
  ppList_FILL_FROM_ARRAY(anw, arr_anw2);

  ppList_BEGIN(l1, pos); ppListIterator_NEXT(pos); ppListIterator_NEXT(pos); // pos = 4

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);

  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 2: Splice before element in middle\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);

  printf("\n-------------------------------------------\n\n");

  // Тест 3: вставка src перед хвостом (перед 8)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw3[] = {1,2,4,5,6,7,1,3,6,9,10,11,8}; // вставка перед 8
  ppList_FILL_FROM_ARRAY(anw, arr_anw3);

  ppList_END(l1, pos); // pos указывает на 8 (если END даёт последний узел)

  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);

  printf("Test 3: Splice before tail\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, NULL)\n", begin_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);

  printf("\n-------------------------------------------\n\n");

  // Тест 4: вставка перед NULL (в конец списка)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw4[] = {1,2,4,5,6,7,8,1,3,6,9,10,11}; // вставка в конец
  ppList_FILL_FROM_ARRAY(anw, arr_anw4);

  ppList_END(l1, pos); ppListIterator_NEXT(pos); // pos->node = NULL
  ppList_BEGIN(l2, src_begin);
  ppList_END(l2, src_end); ppListIterator_NEXT(src_end);
  
  ppListIterator_GET_VAL(begin_val, src_begin);
  printf("Test 4: Splice before NULL (insert after tail)\n");
  printf("Dest position: before NULL (after tail)\n");
  printf("Src range: [%d, NULL)\n", begin_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);

  printf("\n-------------------------------------------\n\n");

  // Тест 5: вставка диапазона из одного элемента перед головой (перед 1)
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);
  int arr_anw5[] = {3,1,2,4,5,6,7,8};
  ppList_FILL_FROM_ARRAY(anw, arr_anw5);

  int arr_anw2_5[] = {1,6,9,10,11};
  ppList_FILL_FROM_ARRAY(anw2, arr_anw2_5);

  ppList_BEGIN(l1, pos); // pos = 1
  ppList_BEGIN(l2, src_begin); ppListIterator_NEXT(src_begin); // src_begin = 3
  ppList_BEGIN(l2, src_end);
  for (int i = 0; i < 2; ++i) ppListIterator_NEXT(src_end); // src_end = 6

  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 5: Splice single element before head\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);

  printf("\n-------------------------------------------\n\n");

  // Тест 6: перемещение диапазона (элементы 2 и 4) перед элементом 7
  ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw); ppList_CLEAR(anw2);

  ppList_FILL_FROM_ARRAY(l1, arr1);
  ppList_FILL_FROM_ARRAY(l2, arr2);

  int arr_anw6[] = {1, 5, 6, 2, 4, 7, 8}; // вставка перед 7
  ppList_FILL_FROM_ARRAY(anw, arr_anw6);
  ppList_FILL_FROM_ARRAY(anw2, arr2);

  ppList_BEGIN(l1, pos);
  for (int i = 0; i < 5; ++i) ppListIterator_NEXT(pos); // pos = 7

  ppList_BEGIN(l1, src_begin); ppListIterator_NEXT(src_begin); // src_begin = 2
  ppList_BEGIN(l1, src_end);
  for (int i = 0; i < 3; ++i) ppListIterator_NEXT(src_end); // src_end = 5

  ppListIterator_GET_VAL(pos_val, pos);
  ppListIterator_GET_VAL(begin_val, src_begin);
  ppListIterator_GET_VAL(end_val, src_end);
  printf("Test 6: Splicing within one list without overlapping\n");
  printf("Dest position: before %d\n", pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);

  printf("\n-------------------------------------------\n\n");

  // Тест 7: вставка пустого src-диапазона
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
  printf("Test 7: Splice empty src (should do nothing)\n");
  printf("Dest position: before %d\n",pos_val);
  printf("Src range: [%d, %d)\n", begin_val, end_val);

  ppList_SPLICE_BEFORE(pos, src_begin, src_end);
  print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw, (ppList*)&anw2);
  
  printf("\n-------------------------------------------\n\n");

  return 0;
}