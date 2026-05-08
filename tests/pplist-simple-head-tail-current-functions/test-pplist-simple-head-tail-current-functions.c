// test-pplist-simple-head-tail-current-functions.c - тестирование простых функций связанных с head, tail и current
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

void print_list(ppList* l, const char* name) {
  printf("%s: ", name);
  ppList_print2(stdout, l);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  ppList_VAR(int, l);
  int val;

  printf("\n-------------------------------------------\n\n");
  
  // 1. front_current / back_current
  printf("front_current / back_current\n\n");

  // 1.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 1.1: front_current on empty list\n");
  ppList_front_current((ppList*)&l);
  check_condition(l.current == NULL, "current becomes NULL", &errors);

  ppList_back_current((ppList*)&l);
  check_condition(l.current == NULL, "back_current also keeps NULL", &errors);
  printf("\n");

  // 1.2 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 42);
  printf("Test 1.2: front_current on single element\n");
  ppList_front_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(val == 42 && l.current == l.head, "current = 42, points to head", &errors);
  printf("Test 1.3: back_current on single element\n");
  ppList_back_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(val == 42 && l.current == l.tail, "current = 42, points to tail", &errors);
  printf("\n");

  // 1.3 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr[] = {10,20,30,40};
  ppList_FILL_FROM_ARRAY(l, arr);
  printf("Test 1.4: front_current on 4-element list\n");
  ppList_front_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(val == 10 && l.current == l.head, "current = 10 (head)", &errors);
  printf("Test 1.5: back_current on same list\n");
  ppList_back_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(val == 40 && l.current == l.tail, "current = 40 (tail)", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. next_current / prev_current
  printf("next_current / prev_current\n\n");

  // 2.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 2.1: next_current on empty list\n");
  int res = ppList_next_current((ppList*)&l);
  check_condition(res == 0, "returns 0, current remains NULL", &errors);
  printf("Test 2.2: prev_current on empty list\n");
  res = ppList_prev_current((ppList*)&l);
  check_condition(res == 0, "returns 0, current remains NULL", &errors);
  printf("\n");

  // 2.2 Список из одного элемента
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 100);
  printf("Test 2.3: next_current on single element\n");
  res = ppList_next_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(res == 0 && val == 100, "returns 0, current unchanged (100)", &errors);
  printf("Test 2.4: prev_current on single element\n");
  res = ppList_prev_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(res == 0 && val == 100, "returns 0, current unchanged (100)", &errors);
  printf("\n");

  // 2.3 Список из нескольких элементов
  ppList_CLEAR(l);
  int arr2[] = {5,6,7,8};
  ppList_FILL_FROM_ARRAY(l, arr2);
  printf("Test 2.5: step forward through list\n");
  ppList_front_current((ppList*)&l);
  int expected_next[] = {6,7,8};
  for (int i = 0; i < 3; ++i) {
      res = ppList_next_current((ppList*)&l);
      ppList_GET_CURRENT_VAL(val, l);
      char msg[100];
      sprintf(msg, "next_current step %d -> current = %d", i+1, expected_next[i]);
      check_condition(res == 1 && val == expected_next[i], msg, &errors);
  }
  res = ppList_next_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(res == 0 && val == 8 && l.current == l.tail, "next beyond tail returns 0, current stays at tail", &errors);
  printf("Test 2.6: step backward through list\n");
  for (int i = 2; i >= 0; --i) {
      res = ppList_prev_current((ppList*)&l);
      ppList_GET_CURRENT_VAL(val, l);
      char msg[100];
      sprintf(msg, "prev_current step -> current = %d", arr2[i]);
      check_condition(res == 1 && val == arr2[i], msg, &errors);
  }
  res = ppList_prev_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(val, l);
  check_condition(res == 0 && val == 5 && l.current == l.head, "prev before head returns 0, current stays at head", &errors);
  printf("\n-------------------------------------------\n\n");

  // 3. is_head / is_tail 
  printf("is_head / is_tail\n\n");

  // 3.1 Пустой список
  ppList_CLEAR(l);
  printf("Test 3.1: is_head on empty list (current = NULL)\n");
  check_condition(ppList_is_head((ppList*)&l) == 1, "returns 1", &errors);
  check_condition(ppList_is_tail((ppList*)&l) == 1, "returns 1", &errors);
  printf("\n");

  // 3.2 Один элемент
  ppList_CLEAR(l);
  ppList_PUSH_BACK(l, 99);
  ppList_front_current((ppList*)&l);
  printf("Test 3.2: single element\n");
  check_condition(ppList_is_head((ppList*)&l) == 1, "is_head returns 1", &errors);
  check_condition(ppList_is_tail((ppList*)&l) == 1, "is_tail returns 1", &errors);
  printf("\n");

  // 3.3 Несколько элементов
  ppList_CLEAR(l);
  ppList_FILL_FROM_ARRAY(l, arr);
  ppList_front_current((ppList*)&l);
  printf("Test 3.3: head element\n");
  check_condition(ppList_is_head((ppList*)&l) == 1, "is_head = 1", &errors);
  check_condition(ppList_is_tail((ppList*)&l) == 0, "is_tail = 0", &errors);
  ppList_next_current((ppList*)&l);
  printf("Test 3.4: middle element\n");
  check_condition(ppList_is_head((ppList*)&l) == 0, "is_head = 0", &errors);
  check_condition(ppList_is_tail((ppList*)&l) == 0, "is_tail = 0", &errors);
  ppList_back_current((ppList*)&l);
  printf("Test 3.5: tail element\n");
  check_condition(ppList_is_head((ppList*)&l) == 0, "is_head = 0", &errors);
  check_condition(ppList_is_tail((ppList*)&l) == 1, "is_tail = 1", &errors);
  printf("\n-------------------------------------------\n\n");

  //4. Макросы GET_FRONT_VAL / GET_BACK_VAL / GET_CURRENT_VAL
  printf("GET_FRONT_VAL / GET_BACK_VAL / GET_CURRENT_VAL\n\n");
  ppList_CLEAR(l);
  int init[] = {7, 8, 9};
  ppList_FILL_FROM_ARRAY(l, init);
  printf("Test 4.1: retrieving values (list = 7 8 9)\n");
  int front, back, cur;
  ppList_GET_FRONT_VAL(front, l);
  ppList_GET_BACK_VAL(back, l);
  ppList_GET_CURRENT_VAL(cur, l);
  check_condition(front == 7, "front = 7", &errors);
  check_condition(back == 9, "back = 9", &errors);
  check_condition(cur == 9, "current = 9 (tail)", &errors);

  printf("\nTest 4.2: front/back do not change current\n");
  ppList_front_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(cur, l);
  check_condition(cur == 7, "after front_current, current = 7", &errors);
  ppList_GET_FRONT_VAL(front, l);
  ppList_GET_CURRENT_VAL(cur, l);
  check_condition(cur == 7, "after GET_FRONT_VAL, current still 7", &errors);
  ppList_GET_BACK_VAL(back, l);
  ppList_GET_CURRENT_VAL(cur, l);
  check_condition(cur == 7, "after GET_BACK_VAL, current still 7", &errors);

  printf("\nTest 4.3: GET_CURRENT_VAL after moving current\n");
  ppList_next_current((ppList*)&l);
  ppList_GET_CURRENT_VAL(cur, l);
  check_condition(cur == 8, "after next, current = 8", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}