// test-pplist-remove.c - тестирование функции remove обобщенного списка ppList
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>;

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


//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);

  printf("REMOVE\n\n");

  // 1. Удаление из пустого списка
  printf("Test 1: Remove from empty list\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 5);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 2. Удаление из списка с одним элементом (совпадает)
  printf("Test 2: Remove single matching element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 42);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 42);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 3. Удаление из списка с одним элементом (не совпадает)
  printf("Test 3: Remove single non-matching element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 100);
  ppList_PUSH_BACK(anw, 100);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 99);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 4. Удаление всех вхождений из середины (несколько одинаковых подряд)
  printf("Test 4: Remove consecutive duplicates from middle\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr4[] = {1,2,2,2,3,4};
  ppList_FILL_FROM_ARRAY(l, arr4);
  int expected4[] = {1,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected4);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 2);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 5. Удаление головы
  printf("Test 5: Remove head element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr5[] = {5,10,15,20};
  ppList_FILL_FROM_ARRAY(l, arr5);
  int expected5[] = {10,15,20};
  ppList_FILL_FROM_ARRAY(anw, expected5);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 5);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 6. Удаление хвоста
  printf("Test 6: Remove tail element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr6[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr6);
  int expected6[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(anw, expected6);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 40);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 7. Удаление всех элементов (список полностью совпадает)
  printf("Test 7: Remove all elements (all match)\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr7[] = {7,7,7};
  ppList_FILL_FROM_ARRAY(l, arr7);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 7);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n");

  // 8. Удаление не последовательных дубликатов (все вхождения)
  printf("Test 8: Remove non-consecutive duplicates\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr8[] = {1,2,1,3,1,4};
  ppList_FILL_FROM_ARRAY(l, arr8);
  int expected8[] = {2,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected8);
  print_list((ppList*)&l, "l");
  SET_FOUNDATION(l, 1);
  ppList_remove((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}