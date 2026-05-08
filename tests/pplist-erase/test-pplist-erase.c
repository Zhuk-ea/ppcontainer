// test-pplist-erase.c - тестирование функции erase обобщенного списка ppList
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
  int val;

  printf("\n-------------------------------------------\n\n");
  // Тесты для ppListIterator_erase
  printf("ERASE\n\n");

  // 1. Удаление первого элемента (головы)
  printf("Test 1: Erase head element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr1[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr1);
  int expected1[] = {20,30};
  ppList_FILL_FROM_ARRAY(anw, expected1);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_erase((ppListIterator*)&it);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 20, "iterator points to 20", &errors);
  printf("\n");

  // 2. Удаление последнего элемента (хвоста)
  printf("Test 2: Erase tail element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr2[] = {10,20,30};
  ppList_FILL_FROM_ARRAY(l, arr2);
  int expected2[] = {10,20};
  ppList_FILL_FROM_ARRAY(anw, expected2);
  print_list((ppList*)&l, "l");
  ppList_END(l, it);
  ppListIterator_erase((ppListIterator*)&it);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 20, "iterator points to 20", &errors);
  printf("\n");

  // 3. Удаление элемента в середине
  printf("Test 3: Erase middle element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr3[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr3);
  int expected3[] = {10,30,40};
  ppList_FILL_FROM_ARRAY(anw, expected3);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_NEXT(it);
  ppListIterator_erase((ppListIterator*)&it);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  ppListIterator_GET_VAL(val, it);
  check_condition(val == 30, "iterator points to 30", &errors);
  printf("\n");

  // 4. Удаление единственного элемента
  printf("Test 4: Erase single element\n");
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 42);
  ppList_CLEAR(anw);
  print_list((ppList*)&l, "l");
  ppList_BEGIN(l, it);
  ppListIterator_erase((ppListIterator*)&it);
  check_lists((ppList*)&l, (ppList*)&anw, &errors);
  check_condition(it.node == NULL, "iterator is NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}