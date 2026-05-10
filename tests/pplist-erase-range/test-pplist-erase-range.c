// test-pplist-erase-range.c - тестирование удаления диапазона итераторами ppList
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Специализация для int
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
  printf("\n-------------------------------------------\n");
  printf("ERASE_RANGE\n\n");

  ppList_VAR(int, list);
  ppListIterator_VAR(int, it_begin);
  ppListIterator_VAR(int, it_end);
  uint32_t removed;

  int all_vals[] = {10, 20, 30, 40, 50, 60, 70};

  //1. Удаление диапазона из середины
  printf("1. Erase range from middle\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  print_list((ppList*)&list, "initial");

  ppList_BEGIN(list, it_begin);
  ppListIterator_NEXT(it_begin);
  ppListIterator_NEXT(it_begin);
  ppListIterator_VAR(int, it_end_tmp);
  ppList_BEGIN(list, it_end_tmp);
  for (int i = 0; i < 5; i++) {
    ppListIterator_NEXT(it_end_tmp);
  }
  it_end = it_end_tmp;
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 3, "removed 3 elements (30,40,50)", &errors);
  int exp1[] = {10,20,60,70};
  ppList_VAR(int, expected1);
  ppList_FILL_FROM_ARRAY(expected1, exp1);
  check_list((ppList*)&list, (ppList*)&expected1, "list after erase", &errors);

  int val;
  ppListIterator_GET_VAL(val, it_begin);
  check_condition(val == 20, "begin iterator moved to predecessor (20)", &errors);
  ppListIterator_GET_VAL(val, it_end);
  check_condition(val == 60, "end iterator unchanged (60)", &errors);
  printf("\n");

  // 2. Удаление с начала (begin = head)
  printf("2. Erase range from beginning\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  ppList_BEGIN(list, it_end);
  for (int i = 0; i < 3; i++) {
    ppListIterator_NEXT(it_end);
  }
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 3, "removed 3 elements (10,20,30)", &errors);
  int exp2[] = {40,50,60,70};
  ppList_VAR(int, expected2);
  ppList_FILL_FROM_ARRAY(expected2, exp2);
  check_list((ppList*)&list, (ppList*)&expected2, "list after erase", &errors);
  ppListIterator_GET_VAL(val, it_begin);
  check_condition(val == 40, "begin iterator becomes end (40)", &errors);
  printf("\n");

  // 3. Удаление до конца (end == NULL)
  printf("3. Erase range to the end\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  for (int i = 0; i < 4; i++) {
    ppListIterator_NEXT(it_begin);
  }
  it_end.node = NULL; 
  it_end.list = (ppList*)&list;
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 3, "removed 3 elements (50,60,70)", &errors);
  int exp3[] = {10,20,30,40};
  ppList_VAR(int, expected3);
  ppList_FILL_FROM_ARRAY(expected3, exp3);
  check_list((ppList*)&list, (ppList*)&expected3, "list after erase", &errors);
  ppListIterator_GET_VAL(val, it_begin);
  check_condition(val == 40, "begin iterator moved to predecessor (40)", &errors);
  printf("\n");

  // 4. Удаление всего списка
  printf("4. Erase whole list\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  it_end.node = NULL;
  it_end.list = (ppList*)&list;
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 7, "removed all 7 elements", &errors);
  check_condition(ppList_empty((ppList*)&list) == 1, "list becomes empty", &errors);
  check_condition(it_begin.node == NULL, "begin iterator becomes NULL (end)", &errors);
  printf("\n");

  // 5. Пустой диапазон
  printf("5. Empty range (begin == end)\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  ppList_BEGIN(list, it_end);
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 0, "removed 0 elements", &errors);
  check_list((ppList*)&list, (ppList*)&list, "list unchanged", &errors);
  printf("\n");

  // 6. Некорректные итераторы
  printf("6. Invalid iterators\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  it_end.node = NULL;
  it_end.list = NULL;
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 0, "end iterator invalid -> 0", &errors);
  check_list((ppList*)&list, (ppList*)&list, "list unchanged", &errors);

  ppList_VAR(int, other);
  ppList_FILL_FROM_ARRAY(other, exp1);
  ppList_BEGIN(other, it_end);
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(removed == 0, "different lists -> 0", &errors);
  printf("\n");

  // 7. Проверка корректировки current
  printf("7. Current pointer adjustment\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  ppListIterator_NEXT(it_begin); ppListIterator_NEXT(it_begin);
  list.current = it_begin.node;
  ppListIterator_VAR(int, it_begin2);
  ppListIterator_VAR(int, it_end2);
  ppList_BEGIN(list, it_begin2);
  ppListIterator_NEXT(it_begin2);
  ppList_BEGIN(list, it_end2);
  for (int i = 0; i < 5; i++) {
    ppListIterator_NEXT(it_end2);
  }
  removed = ppListIterator_ERASE_RANGE(it_begin2, it_end2);
  check_condition(removed == 4, "removed 20,30,40,50", &errors);
  ppList_VAR(int, expected_current);
  ppList_PUSH_BACK(expected_current, 60);
  int current_val;
  ppList_current((ppList*)&list);
  current_val = list.@;
  check_condition(current_val == 60, "current moved to next element (60)", &errors);
  printf("\n");

  // 8. Обновление head/tail при удалении крайних
  printf("8. Head/tail update\n\n");
  ppList_CLEAR(list);
  ppList_FILL_FROM_ARRAY(list, all_vals);
  ppList_BEGIN(list, it_begin);
  ppList_BEGIN(list, it_end);
  for (int i = 0; i < 3; i++) {
    ppListIterator_NEXT(it_end);
  }
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(list.head->data[0] == 40, "new head is 40", &errors);
  ppList_BEGIN(list, it_begin);
  for (int i = 0; i < 2; i++) ppListIterator_NEXT(it_begin);
  it_end.node = NULL;
  removed = ppListIterator_ERASE_RANGE(it_begin, it_end);
  check_condition(list.tail->data[0] == 50, "new tail is 50", &errors);

  printf("Total errors: %d\n", errors);
  printf("\n-------------------------------------------\n");
  return errors;
}