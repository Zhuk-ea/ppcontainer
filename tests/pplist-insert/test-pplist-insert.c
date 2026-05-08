// test-pplist-insert.c - тестирование функций "семейства" insert
#include <stdio.h>
#include <string.h>
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

void check_lists(ppList* l, ppList* anw, int* errors) {
  if (ppList_is_equal(l, anw, sizeof(int))) {
    printf("Correct | l: ");
  } else {
    printf("Incorrect | l: ");
    (*errors)++;
  }
  ppList_print2(stdout, l);
}

void print_list(ppList* l, const char* label) {
  printf("%s: ", label);
  ppList_print2(stdout, l);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  ppListIterator_VAR(int, it);

  printf("\n-------------------------------------------\n\n");

  // 1. Тесты для ppListIterator_insert_after
  printf("INSERT_AFTER\n\n");

  // 1.1 Вставка после первого элемента (список из нескольких)
  printf("Test 1.1: Insert after first element (15 after 10)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr1[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr1);
  int expected1[] = {10,15,20,30};
  ppList_FILL_FROM_ARRAY(anw, expected1);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_INSERT_AFTER(it, 15);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 1.2 Вставка после последнего элемента (аналог push_back)
  printf("Test 1.2: Insert after tail (4 after 3)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr2);
  int expected2[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected2);
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_INSERT_AFTER(it, 4);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 1.3 Вставка после элемента в середине
  printf("Test 1.3: Insert after middle element (7 after 6)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {5,6,8,9};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {5,6,7,8,9};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_NEXT(it);
  ppListIterator_INSERT_AFTER(it, 7);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 1.4 Вставка после элемента в списке из одного элемента
  printf("Test 1.4: Insert after single element (200 after 100)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 100);
  int expected4[] = {100,200};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_INSERT_AFTER(it, 200);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для ppListIterator_insert_before
  printf("INSERT_BEFORE\n\n");

  // 2.1 Вставка перед первым элементом (аналог push_front)
  printf("Test 2.1: Insert before first element (10 before 20)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_INSERT_BEFORE(it, 10);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 2.2 Вставка перед последним элементом
  printf("Test 2.2: Insert before tail (3 before 4)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {1,2,4};
  ppList_FILL_FROM_ARRAY(l, arr6);
  int expected6[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected6);
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_INSERT_BEFORE(it, 3);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 2.3 Вставка перед элементом в середине
  printf("Test 2.3: Insert before middle element (30 before 40)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr7[] = {10,20,40,50};
  ppList_FILL_FROM_ARRAY(l, arr7);
  int expected7[] = {10,20,30,40,50};
  ppList_FILL_FROM_ARRAY(anw, expected7);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_NEXT(it); ppListIterator_NEXT(it);
  ppListIterator_INSERT_BEFORE(it, 30);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n");

  // 2.4 Вставка перед элементом в списке из одного элемента
  printf("Test 2.4: Insert before single element (25 before 50)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 50);
  int expected8[] = {25,50};
  ppList_FILL_FROM_ARRAY(anw, expected8);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_INSERT_BEFORE(it, 25);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}