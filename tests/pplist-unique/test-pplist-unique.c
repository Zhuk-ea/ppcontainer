// test-pplist-unique.c - тестирование функции unique для списка
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Специализация для int
//==============================================================================

ppList+<int;>;

//------------------------------------------------------------------------------
// Обработчик вывода
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}

//------------------------------------------------------------------------------
// Универсальные вспомогательные функции
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

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  ppList_VAR(int, empty);

  // Тесты для ppList_unique
  printf("UNIQUE\n\n");

  // Тест 1: пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test 1: Empty list\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&empty, "l", &errors);
  printf("\n");

  // Тест 2: список из одного элемента
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {42};
  ppList_FILL_FROM_ARRAY(l, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr2);
  printf("Test 2: Single element\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 3: все элементы различны (нет последовательных дубликатов)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(l, arr3);
  ppList_FILL_FROM_ARRAY(anw, arr3);
  printf("Test 3: All distinct, no consecutive duplicates\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 4: последовательные дубликаты в середине
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {1,2,2,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr4);
  int expected4[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  printf("Test 4: Consecutive duplicates in middle\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 5: дубликаты в начале и в конце
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {1,1,2,3,3,3,4,5,5};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  printf("Test 5: Duplicates at head and tail\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 6: все элементы одинаковы
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {7,7,7,7,7};
  ppList_FILL_FROM_ARRAY(l, arr6);
  int expected6[] = {7};
  ppList_FILL_FROM_ARRAY(anw, expected6);
  printf("Test 6: All elements identical\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 7: не последовательные дубликаты (не удаляются)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr7[] = {1,2,1,2,1};
  ppList_FILL_FROM_ARRAY(l, arr7);
  ppList_FILL_FROM_ARRAY(anw, arr7);
  printf("Test 7: Non-consecutive duplicates (not removed)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_ENIQUE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}