// test-ppmap-insert.c - тестирование вставки в обобщённое отображение ppMap
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
// Обработчик вывода
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n");
  printf("INSERT\n\n");

  ppMap_VAR(IntPair, map);
  ppMap_VAR(IntPair, expected);
  ppMap_init((ppMap*)&map, cmp_int);
  ppMap_init((ppMap*)&expected, cmp_int);

  // 1. Вставка в пустое отображение
  printf("Test 1: Insert into empty map\n");
  ppMap_INSERT(map, 10, 100);
  ppMap_INSERT(expected, 10, 100);
  print_map((ppMap*)&map, "map");
  check_map_int_content((ppMap*)&map, (int[]){10}, (int[]){100}, 1, &errors, "insert single element");
  printf("\n");

  // 2. Вставка нескольких элементов (проверка порядка и размера)
  printf("Test 2: Insert multiple elements\n");
  ppMap_INSERT(map, 5, 50);
  ppMap_INSERT(map, 15, 150);
  ppMap_INSERT(map, 3, 30);
  ppMap_INSERT(map, 20, 200);
  ppMap_INSERT(expected, 5, 50);
  ppMap_INSERT(expected, 15, 150);
  ppMap_INSERT(expected, 3, 30);
  ppMap_INSERT(expected, 20, 200);
  print_map((ppMap*)&map, "map");
  int exp_keys[] = {3,5,10,15,20};
  int exp_vals[] = {30,50,100,150,200};
  check_map_int_content((ppMap*)&map, exp_keys, exp_vals, 5, &errors, "multiple inserts in order");
  check_condition(ppMap_size((ppMap*)&map) == 5, "size = 5 after inserts", &errors);
  printf("\n");

  // 3. Вставка существующего ключа (замена значения)
  printf("Test 3: Insert existing key (value update)\n");
  ppMap_INSERT(map, 10, 999);
  ppMap_INSERT(expected, 10, 999);
  print_map((ppMap*)&map, "map");
  int exp_keys2[] = {3,5,10,15,20};
  int exp_vals2[] = {30,50,999,150,200};
  check_map_int_content((ppMap*)&map, exp_keys2, exp_vals2, 5, &errors, "update existing key");
  check_condition(ppMap_size((ppMap*)&map) == 5, "size unchanged after update", &errors);
  printf("\n");

  // 4. Вставка большого количества элементов (проверка роста дерева)
  printf("Test 4: Insert many elements (stress)\n");
  ppMap_CLEAR(map);
  for (int i = 0; i < 100; i++) {
    ppMap_INSERT(map, i, i * 10);
  }
  check_condition(ppMap_size((ppMap*)&map) == 100, "size = 100 after 100 inserts", &errors);
  int val;
  if (ppMap_FIND(map, 42, val)) {
    check_condition(val == 420, "key 42 has value 420", &errors);
  } else {
    check_condition(0, "key 42 not found", &errors);
  }
  printf("\n");

  printf("-------------------------------------------\n");
  printf("Total errors: %d\n", errors);
  return errors;
}