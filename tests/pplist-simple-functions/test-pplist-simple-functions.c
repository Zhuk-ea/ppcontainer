// test-pplist-simple-functions.c - тестирование простых функций (init, empty, size, clear, replace_current)
#include <stdio.h>
#include "pplist.h"
#include "test-pplist-common.h"

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
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppList_VAR(int, l);
  ppList_VAR(int, anw);

  // 1. Тест ppList_empty
  printf("EMPTY\n\n");

  // 1.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 1.1: empty list\n");
  if (ppList_empty((ppList*)&l)) {
    printf("Correct | list is empty\n");
  } else {
    printf("Incorrect | list is not empty\n");
    errors++;
  }

  // 1.2 Непустой список
  int arr[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr);
  printf("Test 1.2: non-empty list\n");
  if (!ppList_empty((ppList*)&l)) {
    printf("Correct | list is not empty\n");
  } else {
    printf("Incorrect | list is empty\n");
    errors++;
  }

  printf("\n-------------------------------------------\n\n");

  // 2. Тест ppList_size
  printf("SIZE\n\n");

  ppList_CLEAR(l);
  printf("Test 2.1: size = %u (expected 0)\n", ppList_size((ppList*)&l));
  ppList_PUSH_BACK(l, 10);
  printf("Test 2.2: after push_back, size = %u (expected 1)\n", ppList_size((ppList*)&l));
  ppList_PUSH_FRONT(l, 20);
  printf("Test 2.3: after push_front, size = %u (expected 2)\n", ppList_size((ppList*)&l));
  ppList_clear((ppList*)&l);
  printf("Test 2.4: after clear, size = %u (expected 0)\n", ppList_size((ppList*)&l));
  printf("\n-------------------------------------------\n\n");

  // 3. Тест ppList_clear
  printf("CLEAR\n\n");

  ppList_FILL_FROM_ARRAY(l, arr);
  ppList_CLEAR(anw);
  printf("Test 3: before clear\n");
  print_list((ppList*)&l, "l");
  ppList_clear((ppList*)&l);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  printf("\n-------------------------------------------\n\n");

  // 4. Тест ppList_replace_current
  printf("REPLACE_CURRENT\n\n");

  // 4.1 Непустой список, замена текущего (хвоста)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 5);
  ppList_PUSH_BACK(l, 6);
  ppList_REPLACE_CURRENT(l, 100);
  ppList_PUSH_BACK(anw, 5);
  ppList_PUSH_BACK(anw, 100);
  printf("Test 4.1: replace current in non-empty list\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  int cur_val;
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 100, "current after replace = 100", &errors);
  printf("\n");

  // 4.2 Пустой список, замена не должна ничего делать
  ppList_CLEAR(l);
  printf("Test 4.2: replace current in empty list\n");
  int res = ppList_replace_current((ppList*)&l);
  check_condition(res == 0, "returns 0 (no replacement)", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}