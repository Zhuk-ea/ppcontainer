// test-pplist-unique.c - тестирование функции nique для списка
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
    ppList_VAR(int, empty); // пустой список для сравнения

    // --------------------------------------------------------------
    // Тест 1: пустой список
    ppList_CLEAR(l); ppList_CLEAR(anw);
    printf("Test 1: Empty list\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&empty);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 2: список из одного элемента
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr2[] = {42};
    ppList_FILL_FROM_ARRAY(l, arr2);
    ppList_FILL_FROM_ARRAY(anw, arr2);
    printf("Test 2: Single element\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 3: все элементы различны (нет последовательных дубликатов)
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr3[] = {1,2,3,4,5};
    ppList_FILL_FROM_ARRAY(l, arr3);
    ppList_FILL_FROM_ARRAY(anw, arr3);
    printf("Test 3: All distinct, no consecutive duplicates\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 4: последовательные дубликаты в середине
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr4[] = {1,2,2,2,3,4};
    ppList_FILL_FROM_ARRAY(l, arr4);
    int expected4[] = {1,2,3,4};
    ppList_FILL_FROM_ARRAY(anw, expected4);
    printf("Test 4: Consecutive duplicates in middle\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 5: дубликаты в начале и в конце
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr5[] = {1,1,2,3,3,3,4,5,5};
    ppList_FILL_FROM_ARRAY(l, arr5);
    int expected5[] = {1,2,3,4,5};
    ppList_FILL_FROM_ARRAY(anw, expected5);
    printf("Test 5: Duplicates at head and tail\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 6: все элементы одинаковы
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr6[] = {7,7,7,7,7};
    ppList_FILL_FROM_ARRAY(l, arr6);
    int expected6[] = {7};
    ppList_FILL_FROM_ARRAY(anw, expected6);
    printf("Test 6: All elements identical\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    // --------------------------------------------------------------
    // Тест 7: не последовательные дубликаты (не удаляются)
    ppList_CLEAR(l); ppList_CLEAR(anw);
    int arr7[] = {1,2,1,2,1};
    ppList_FILL_FROM_ARRAY(l, arr7);
    ppList_FILL_FROM_ARRAY(anw, arr7);
    printf("Test 7: Non-consecutive duplicates (not removed)\n");
    printf("l: ");
    ppList_print2(stdout, (ppList*)&l);
    printf("\n");
    ppList_ENIQUE(l);
    print_test_results((ppList*)&l, (ppList*)&anw);
    printf("\n-------------------------------------------\n\n");

    return 0;
}