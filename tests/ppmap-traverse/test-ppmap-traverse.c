// test-ppmap-traverse.c - тестирование обхода (traverse) обобщённого отображения ppMap
#include <stdio.h>
#include "ppmap.h"
#include "test-ppmap-common.h"

//==============================================================================
// Специализация для int -> int
//==============================================================================
typedef struct IntPair {
  int key;
  int value;
} IntPair;

ppMap+<IntPair;>;

//------------------------------------------------------------------------------
// Обработчик вывода (для отладочной печати)
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
// Глобальные переменные для проверки порядка
static int last_key = -1;
static int called = 0;

void reset_traverse_state(void) {
  last_key = -1;
  called = 0;
}

void empty_cb(void* key, void* value) {
  (void)key; (void)value;
  called = 1;
}

void check_sorted_callback(void* key, void* value) {
  (void)value;
  int k = *(int*)key;
  if (k <= last_key) {
    printf("Incorrect order: %d after %d\n", k, last_key);
    exit(1);
  }
  last_key = k;
}

//==============================================================================
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n");
  printf("TRAVERSE\n\n");

  ppMap_VAR(IntPair, map);
  ppMap_init((ppMap*)&map, cmp_int);

  // 1. Вставка в произвольном порядке
  printf("Test 1: Insert elements in random order\n");
  int keys[] = {50, 20, 70, 10, 30, 60, 80};
  int vals[] = {500, 200, 700, 100, 300, 600, 800};
  for (int i = 0; i < 7; i++) {
    ppMap_INSERT(map, keys[i], vals[i]);
  }
  print_map((ppMap*)&map, "map after inserts");
  test_check_condition(ppMap_size((ppMap*)&map) == 7, "size = 7 after inserts", &errors);
  printf("\n");

  // 2. Обход с проверкой порядка
  printf("Test 2: Traverse and verify sorted order\n");
  reset_traverse_state();
  ppMap_traverse((ppMap*)&map, check_sorted_callback);
  test_check_condition(1, "traverse passes sorted order check", &errors);
  printf("\n");

  // 3. Проверка обхода с user_data (сбор пар)
  printf("Test 3: traverse_with_data collects correct key-value pairs\n");
  int expected_keys[] = {10, 20, 30, 50, 60, 70, 80};
  int expected_vals[] = {100, 200, 300, 500, 600, 700, 800};
  check_map_int_content((ppMap*)&map, expected_keys, expected_vals, 7, &errors, "collected pairs match expected");
  printf("\n");


  // 3. Обход очищенного map
  printf("Test 4: Clear map and traverse\n");
  ppMap_clear((ppMap*)&map);
  test_check_condition(ppMap_empty((ppMap*)&map) == 1, "map becomes empty", &errors);
  reset_traverse_state();
  ppMap_traverse((ppMap*)&map, empty_cb);
  test_check_condition(called == 0, "traverse on empty map does not call callback", &errors);
  printf("\n");

  // 5. Обход после вставки одного элемента
  printf("Test 5: Traverse after single insert\n");
  ppMap_INSERT(map, 42, 4242);
  reset_traverse_state();
  ppMap_traverse((ppMap*)&map, check_sorted_callback);
  test_check_condition(1, "single element traversal OK", &errors);
  int val;
  ppMap_FIND(map, 42, val);
  test_check_condition(val == 4242, "value 42->4242 present", &errors);
  printf("\n");

  // 6. Обход после удаления
  printf("Test 6: Traverse after erasing an element\n");
  ppMap_INSERT(map, 10, 100);
  ppMap_INSERT(map, 30, 300);
  ppMap_ERASE(map, 42);
  int exp_keys_after[] = {10, 30};
  int exp_vals_after[] = {100, 300};
  check_map_int_content((ppMap*)&map, exp_keys_after, exp_vals_after, 2,  &errors, "map after erase (10,30)");
  reset_traverse_state();
  ppMap_traverse((ppMap*)&map, check_sorted_callback);
  test_check_condition(1, "traversal after erase works", &errors);
  printf("\n");

  printf("\n-------------------------------------------\n");
  printf("Total errors: %d\n", errors);
  return errors;
}