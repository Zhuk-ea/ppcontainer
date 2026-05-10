// test-ppmap-at.c - тестирование функции at (доступ по ключу с проверкой существования)
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
// Обработчик вывода (не критичен для теста, но нужен для обобщённой печати)
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n");
  printf("TEST ppMap_AT\n\n");

  ppMap_VAR(IntPair, map);
  ppMap_init((ppMap*)&map, cmp_int);

  // Подготовка: вставляем несколько пар
  int keys[] = {10, 20, 30, 40, 50};
  int vals[] = {100, 200, 300, 400, 500};
  for (int i = 0; i < 5; i++) {
    ppMap_INSERT(map, keys[i], vals[i]);
  }
  print_map((ppMap*)&map, "initial map (10..50)");

  // 1. Успешное получение значения для существующего ключа
  printf("\nTest 1: at() for existing keys\n");

  for (int i = 0; i < 5; i++) {
    ppMap_AT(map, keys[i]);  // после этого в специализации лежит значение
    int retrieved = map.@.value;
    char msg[64];
    sprintf(msg, "at(%d) returns %d", keys[i], retrieved);
    test_check_condition(retrieved == vals[i], msg, &errors);
  }

  // 2. Проверка, что at() не изменяет отображение (размер и содержимое)
  printf("\nTest 2: at() does not modify map\n");
  int exp_keys[] = {10,20,30,40,50};
  int exp_vals[] = {100,200,300,400,500};
  check_map_int_content((ppMap*)&map, exp_keys, exp_vals, 5, &errors, "map unchanged after at() calls");
  test_check_condition(ppMap_size((ppMap*)&map) == 5,"size remains 5", &errors);

  // 3. Повторный вызов at() для того же ключа
  printf("\nTest 3: multiple at() calls for same key\n");
  ppMap_AT(map, 30);
  int val1 = map.@.value;
  ppMap_AT(map, 30);
  int val2 = map.@.value;
  test_check_condition(val1 == 300 && val2 == 300, "consistent value retrieval", &errors);

  // 4. Использование at() в выражениях
  printf("\nTest 4: at() then read value\n");
  ppMap_AT(map, 20);
  test_check_condition(map.@.value == 200, "value after at(20) is 200", &errors);

  printf("\n-------------------------------------------\n");
  printf("Total errors: %d\n", errors);
  return errors;
}