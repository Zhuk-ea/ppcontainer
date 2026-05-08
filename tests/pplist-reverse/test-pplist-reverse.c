// test-pplist-reverse.c - тестирование функции reverse для списка
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
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);
  ppList_VAR(int, empty);

  // Тесты для ppList_reverse
  printf("REVERSE\n\n");

  // Тест 1: пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test 1: empty list\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&empty, "l", &errors);
  printf("\n");

  // Тест 2: один элемент
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {42};
  ppList_FILL_FROM_ARRAY(l, arr2);
  ppList_FILL_FROM_ARRAY(anw, arr2);
  printf("Test 2: single element\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 3: два элемента
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {1,2};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {2,1};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  printf("Test 3: two elements\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 4: три элемента (нечётное)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr4);
  int expected4[] = {3,2,1};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  printf("Test 4: three elements (odd)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 5: четыре элемента (чётное)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {4,3,2,1};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  printf("Test 5: four elements (even)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // Тест 6: разворот уже развёрнутого (должен вернуть исходный)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {5,6,7,8};
  ppList_FILL_FROM_ARRAY(l, arr6);
  ppList_FILL_FROM_ARRAY(anw, arr6);
  printf("Test 6: reverse twice (should restore original)\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_REVERSE(l);
  ppList_REVERSE(l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}