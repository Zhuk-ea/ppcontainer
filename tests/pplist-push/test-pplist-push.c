// test-pplist-push.c - тестирование семейства функций push (back, front, after_current, before_current)
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>;
ppListIterator+<int;>;

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
  int cur_val;

  // 1. Тесты для PUSH_BACK
  printf("PUSH_BACK\n\n");

  // 1.1 Пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test push_back on empty list:\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_PUSH_BACK(l, 10);
  ppList_PUSH_BACK(anw, 10);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 10, "current after push = 10", &errors);
  printf("\n");

  // 1.2 Непустой список, несколько вставок подряд
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int arr_back[] = {1,2,3};
  for (int i = 0; i < 3; ++i) {
    ppList_PUSH_BACK(l, arr_back[i]);
    ppList_PUSH_BACK(anw, arr_back[i]);
  }
  printf("Test push_back sequence: 1,2,3\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 3, "current after last push = 3", &errors);
  printf("\n");

  // 1.3 Проверка, что current всегда указывает на вставленный элемент
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 5);
  ppList_PUSH_BACK(l, 7);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 7, "after push_back 7, current = 7", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. Тесты для PUSH_FRONT
  printf("PUSH_FRONT\n\n");

  // 2.1 Пустой список
  ppList_CLEAR(l); ppList_CLEAR(anw);
  printf("Test push_front on empty list:\n");
  print_list((ppList*)&l, "l");
  printf("\n");
  ppList_PUSH_FRONT(l, 20);
  ppList_PUSH_FRONT(anw, 20);
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 20, "current after push = 20", &errors);
  printf("\n");

  // 2.2 Непустой список, несколько вставок спереди
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int front_vals[] = {10,20,30};
  for (int i = 0; i < 3; ++i) {
    ppList_PUSH_FRONT(l, front_vals[i]);
  }
  int expected_front[] = {30,20,10};
  ppList_FILL_FROM_ARRAY(anw, expected_front);
  printf("Test push_front sequence: 10,20,30 (pushed front) -> expected: 30,20,10\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  printf("DEBUG: cur_val = %d\n", cur_val);             //-------------------------------------------------------------
  check_condition(cur_val == 30, "current after last push_front = 30", &errors);
  printf("\n");
  printf("-------------------------------------------\n\n");

  // 3. Тесты для PUSH_AFTER_CURRENT
  printf("PUSH_AFTER_CURRENT\n\n");

  // 3.1 Вставка после первого элемента (current = head)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int initial[] = {1,3,4};
  ppList_FILL_FROM_ARRAY(l, initial);
  ppList_front_current((ppList*)&l);
  ppList_PUSH_AFTER_CURRENT(l, 2);
  int expected_after1[] = {1,2,3,4};
  ppList_FILL_FROM_ARRAY(anw, expected_after1);
  printf("Test push_after_current after head (1 -> after):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 2, "current after push = 2", &errors);
  printf("\n");

  // 3.2 Вставка после хвоста (должно работать как push_back)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_FILL_FROM_ARRAY(l, initial);
  ppList_back_current((ppList*)&l);
  ppList_PUSH_AFTER_CURRENT(l, 5);
  int expected_after2[] = {1,3,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected_after2);
  printf("Test push_after_current after tail (push_back equivalent):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 5, "current after push = 5", &errors);
  printf("\n");

  // 3.3 Вставка в середину (current не крайний)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int mid_initial[] = {1,2,4,5};
  ppList_FILL_FROM_ARRAY(l, mid_initial);
  l.current = l.head->next;
  ppList_PUSH_AFTER_CURRENT(l, 3);
  int expected_after3[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected_after3);
  printf("Test push_after_current in the middle (after 2):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 3, "current after push = 3", &errors);
  printf("\n");
  printf("-------------------------------------------\n\n");

  // 4. Тесты для PUSH_BEFORE_CURRENT
  printf("PUSH_BEFORE_CURRENT\n\n");

  // 4.1 Вставка перед хвостом
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int before_init[] = {1,2,4,5};
  ppList_FILL_FROM_ARRAY(l, before_init);
  ppList_back_current((ppList*)&l);
  ppList_PUSH_BEFORE_CURRENT(l, 4);
  int expected_before1[] = {1,2,4,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected_before1);
  printf("Test push_before_current before tail (insert before 5):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 4, "current after push = 4 (inserted node)", &errors);
  printf("\n");

  // 4.2 Вставка перед головой (эквивалент push_front)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  ppList_FILL_FROM_ARRAY(l, before_init);
  ppList_front_current((ppList*)&l);
  ppList_PUSH_BEFORE_CURRENT(l, 0);
  int expected_before2[] = {0,1,2,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected_before2);
  printf("Test push_before_current before head (push_front equivalent):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 0, "current after push = 0", &errors);
  printf("\n");

  // 4.3 Вставка в середину (перед элементом 4)
  ppList_CLEAR(l); ppList_CLEAR(anw);
  int mid_before[] = {1,2,4,5};
  ppList_FILL_FROM_ARRAY(l, mid_before);
  l.current = l.head->next->next;
  ppList_PUSH_BEFORE_CURRENT(l, 3);
  int expected_before3[] = {1,2,3,4,5};
  ppList_FILL_FROM_ARRAY(anw, expected_before3);
  printf("Test push_before_current in the middle (before 4):\n");
  check_list((ppList*)&l, (ppList*)&anw, "l", &errors);
  ppList_GET_CURRENT_VAL(cur_val, l);
  check_condition(cur_val == 3, "current after push = 3", &errors);
  printf("\n");
  printf("-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}