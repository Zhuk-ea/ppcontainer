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
  if (ppList_is_equal(l, anw, sizeof(int))) printf("Correct ");
  else printf("Incorrect ");

}

void print_2_lists(ppList* l1, ppList* l2) {
  printf("l1: ");
  ppList_print2(stdout, l1);

  printf("l2: ");
  ppList_print2(stdout, l2);
  printf("\n");
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

//------------------------------------------------------------------------------
int main(void) {
    printf("\n-------------------------------------------\n\n");

    ppList_VAR(int, l1);
    ppList_VAR(int, l2);
    ppList_VAR(int, anw1);
    ppList_VAR(int, anw2);
    ppList_VAR(int, empty);

    // Тест 1: оба списка пусты
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    printf("Test 1: Both lists empty\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&empty, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 2: dest пустой, src непустой
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_src1[] = {1,3,5};
    ppList_FILL_FROM_ARRAY(l2, arr_src1);
    ppList_FILL_FROM_ARRAY(anw1, arr_src1);
    printf("Test 2: dest empty, src non-empty\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 3: dest непустой, src пустой
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_dest1[] = {2,4,6};
    ppList_FILL_FROM_ARRAY(l1, arr_dest1);
    ppList_FILL_FROM_ARRAY(anw1, arr_dest1);
    printf("Test 3: dest non-empty, src empty\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 4: dest == src (один и тот же список)
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_same[] = {1,2,3};
    ppList_FILL_FROM_ARRAY(l1, arr_same);
    ppList_FILL_FROM_ARRAY(anw1, arr_same);
    printf("Test 4: dest == src (same list)\n");
    print_2_lists((ppList*)&l1, (ppList*)&l1);
    ppList_MERGE(l1, l1, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l1, (ppList*)&anw1, (ppList*)&anw1);
    printf("\n-------------------------------------------\n\n");

    // Тест 5: стандартное слияние двух отсортированных списков
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_dest2[] = {1,3,5,7};
    int arr_src2[] = {2,4,6,8};
    ppList_FILL_FROM_ARRAY(l1, arr_dest2);
    ppList_FILL_FROM_ARRAY(l2, arr_src2);
    int arr_expected1[] = {1,2,3,4,5,6,7,8};
    ppList_FILL_FROM_ARRAY(anw1, arr_expected1);
    printf("Test 5: Merge two sorted lists (interleaved)\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 6: src все элементы меньше dest
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_dest3[] = {10,20,30};
    int arr_src3[] = {1,2,3};
    ppList_FILL_FROM_ARRAY(l1, arr_dest3);
    ppList_FILL_FROM_ARRAY(l2, arr_src3);
    int arr_expected2[] = {1,2,3,10,20,30};
    ppList_FILL_FROM_ARRAY(anw1, arr_expected2);
    printf("Test 6: src all elements smaller than dest\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 7: src все элементы больше dest
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_dest4[] = {1,2,3};
    int arr_src4[] = {10,20,30};
    ppList_FILL_FROM_ARRAY(l1, arr_dest4);
    ppList_FILL_FROM_ARRAY(l2, arr_src4);
    int arr_expected3[] = {1,2,3,10,20,30};
    ppList_FILL_FROM_ARRAY(anw1, arr_expected3);
    printf("Test 7: src all elements greater than dest\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 8: слияние с дубликатами
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_dup1[] = {1,2,2,3};
    int arr_dup2[] = {2,3,4};
    ppList_FILL_FROM_ARRAY(l1, arr_dup1);
    ppList_FILL_FROM_ARRAY(l2, arr_dup2);
    int arr_expected4[] = {1,2,2,2,3,3,4};
    ppList_FILL_FROM_ARRAY(anw1, arr_expected4);
    printf("Test 8: Merge with duplicates\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    ppList_MERGE(l1, l2, cmp_int);
    print_test_results((ppList*)&l1, (ppList*)&l2, (ppList*)&anw1, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // Тест 9: слияние неотсортированных списков (только проверка размеров и очистки src)
    ppList_CLEAR(l1); ppList_CLEAR(l2); ppList_CLEAR(anw1); ppList_CLEAR(anw2);
    int arr_unsort1[] = {5,1,9};
    int arr_unsort2[] = {3,7,2};
    ppList_FILL_FROM_ARRAY(l1, arr_unsort1);
    ppList_FILL_FROM_ARRAY(l2, arr_unsort2);
    printf("Test 9: Merge unsorted lists (no sorting guarantee, check sizes and l2 cleared)\n");
    print_2_lists((ppList*)&l1, (ppList*)&l2);
    size_t old_size1 = l1.size;
    size_t old_size2 = l2.size;
    ppList_MERGE(l1, l2, cmp_int);
    if (l1.size == old_size1 + old_size2 && l2.size == 0) printf("Correct ");
    else printf("Incorrect ");
    printf("(l1 size=%zu, l2 size=%zu) ", l1.size, l2.size);
    printf("l1: "); ppList_print2(stdout, (ppList*)&l1); printf("\n");
    printf("\n-------------------------------------------\n\n");

    return 0;
}