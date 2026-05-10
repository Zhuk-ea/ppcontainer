// test-ppmap-erase.c - тестирование удаления из обобщённого отображения ppMap
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
  printf("ERASE\n\n");

  ppMap_VAR(IntPair, map);
  ppMap_init((ppMap*)&map, cmp_int);

  // Подготовка: вставляем 1..7
  for (int i = 1; i <= 7; i++) {
    ppMap_INSERT(map, i, i * 10);
  }
  print_map((ppMap*)&map, "initial map (1..7)");

  // 1. Удаление существующего листового узла
  printf("\nTest 1: Erase leaf node (key=1)\n");
  _Bool erased = ppMap_ERASE(map, 1);
  check_condition(erased == 1, "erase returns 1", &errors);
  int exp_keys1[] = {2,3,4,5,6,7};
  int exp_vals1[] = {20,30,40,50,60,70};
  check_map_int_content((ppMap*)&map, exp_keys1, exp_vals1, 6,
             &errors, "key 1 removed");
  check_condition(ppMap_size((ppMap*)&map) == 6, "size decreased to 6", &errors);

  // 2. Удаление узла с одним ребёнком
  printf("\nTest 2: Erase node with one child (key=2)\n");
  ppMap_ERASE(map, 2);
  int exp_keys2[] = {3,4,5,6,7};
  int exp_vals2[] = {30,40,50,60,70};
  check_map_int_content((ppMap*)&map, exp_keys2, exp_vals2, 5,
             &errors, "key 2 removed");
  check_condition(ppMap_size((ppMap*)&map) == 5, "size = 5", &errors);

  // 3. Удаление узла с двумя детьми (например, 4)
  printf("\nTest 3: Erase node with two children (key=4)\n");
  ppMap_ERASE(map, 4);
  int exp_keys3[] = {3,5,6,7};
  int exp_vals3[] = {30,50,60,70};
  check_map_int_content((ppMap*)&map, exp_keys3, exp_vals3, 4,
             &errors, "key 4 removed, structure preserved");
  check_condition(ppMap_size((ppMap*)&map) == 4, "size = 4", &errors);

  // 4. Удаление корня
  printf("\nTest 4: Erase root (key=5)\n");
  ppMap_ERASE(map, 5);
  int exp_keys4[] = {3,6,7};
  int exp_vals4[] = {30,60,70};
  check_map_int_content((ppMap*)&map, exp_keys4, exp_vals4, 3,
             &errors, "root removed");
  check_condition(ppMap_size((ppMap*)&map) == 3, "size = 3", &errors);

  // 5. Удаление отсутствующего ключа
  printf("\nTest 5: Erase non-existing key\n");
  erased = ppMap_ERASE(map, 99);
  check_condition(erased == 0, "erase returns 0", &errors);
  check_condition(ppMap_size((ppMap*)&map) == 3, "size unchanged", &errors);

  // 6. Удаление всех элементов по одному (проверка очистки)
  printf("\nTest 6: Erase all remaining elements\n");
  ppMap_ERASE(map, 3);
  ppMap_ERASE(map, 6);
  ppMap_ERASE(map, 7);
  check_condition(ppMap_empty((ppMap*)&map) == 1, "map becomes empty", &errors);
  check_condition(ppMap_size((ppMap*)&map) == 0, "size = 0", &errors);

  // 7. Удаление из пустого отображения
  printf("\nTest 7: Erase from empty map\n");
  erased = ppMap_ERASE(map, 10);
  check_condition(erased == 0, "erase on empty returns 0", &errors);
  check_condition(ppMap_empty((ppMap*)&map) == 1, "still empty", &errors);

  printf("\n-------------------------------------------\n");
  printf("Total errors: %d\n", errors);
  return errors;
}