// test-pplist-remove-if.c - тестирование функции remove_if
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

void print_list(ppList* l, const char* label) {
  printf("%s: ", label);
  ppList_print2(stdout, l);
}

//------------------------------------------------------------------------------
// Предикаты для тестов
int is_even(char *data) {
  int val;
  memcpy(&val, data, sizeof(int));
  return val % 2 == 0;
}

int always_true(char *data) {
  return 1;
}

int always_false(char *data) {
  return 0;
}

int equals_10(char *data) {
  int val;
  memcpy(&val, data, sizeof(int));
  return val == 10;
}

int equals_40(char *data) {
  int val;
  memcpy(&val, data, sizeof(int));
  return val == 40;
}

int equals_2(char *data) {
  int val;
  memcpy(&val, data, sizeof(int));
  return val == 2;
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);

  printf("REMOVE_IF\n\n");

  // 1. Пустой список
  printf("Test 1: Remove_if on empty list\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, is_even);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 2. Удаление чётных чисел
  printf("Test 2: Remove even numbers\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {1,2,3,4,5,6};
  ppList_FILL_FROM_ARRAY(l, arr2);
  int expected2[] = {1,3,5};
  ppList_FILL_FROM_ARRAY(anw, expected2);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, is_even);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3. Предикат всегда false (ничего не удаляется)
  printf("Test 3: Predicate always false\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(l, arr3);
  ppList_FILL_FROM_ARRAY(anw, arr3);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, always_false);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 4. Удаление всех элементов (предикат всегда true)
  printf("Test 4: Remove all elements\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr4);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, always_true);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 5. Удаление головы
  printf("Test 5: Remove head element (10)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {20,30,40};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, equals_10);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 6. Удаление хвоста (40)
  printf("Test 6: Remove tail element (40)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr6);
  int expected6[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(anw, expected6);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, equals_40);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 7. Удаление подряд идущих совпадений из середины
  printf("Test 7: Remove consecutive duplicates from middle (2,2,2)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr7[] = {1,2,2,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr7);
  int expected7[] = {1,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected7);
  print_list((ppList*)&l, "l");
  ppList_remove_if((ppList*)&l, equals_2);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}