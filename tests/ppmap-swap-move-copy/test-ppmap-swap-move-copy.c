// test-ppmap-swap-move-copy.c - тестирование функций swap, move, copy обобщённого отображения ppMap
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
// Вспомогательные функции
void print_2_maps(ppMap* m1, ppMap* m2) {
  print_map(m1, "map1");
  print_map(m2, "map2");
}

//==============================================================================
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppMap_VAR(IntPair, map1, cmp_int);
  ppMap_VAR(IntPair, map2, cmp_int);
  ppMap_VAR(IntPair, expected1, cmp_int);
  ppMap_VAR(IntPair, expected2, cmp_int);

  // 1. SWAP
  printf("SWAP\n\n");

  // 1.1 swap двух пустых отображений
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  printf("Test 1.1: swap two empty maps\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_swap((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, NULL, NULL, 0, &errors, "map1 empty after swap");
  check_map_int_content((ppMap*)&map2, NULL, NULL, 0, &errors, "map2 empty after swap");
  printf("\n");

  // 1.2 swap пустого и непустого
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keys1[] = {5,6,7};
  int vals1[] = {50,60,70};
  ppMap_FILL_FROM_ARRAYS(map2, keys1, vals1, 3);
  ppMap_FILL_FROM_ARRAYS(expected1, keys1, vals1, 3);
  // expected2 остаётся пустым
  printf("Test 1.2: swap empty and non-empty\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_swap((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keys1, vals1, 3, &errors, "map1 gets content");
  check_map_int_content((ppMap*)&map2, NULL, NULL, 0, &errors, "map2 becomes empty");
  printf("\n");

  // 1.3 swap двух непустых отображений
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysA[] = {1,2,3};
  int valsA[] = {10,20,30};
  int keysB[] = {10,20};
  int valsB[] = {100,200};
  ppMap_FILL_FROM_ARRAYS(map1, keysA, valsA, 3);
  ppMap_FILL_FROM_ARRAYS(map2, keysB, valsB, 2);
  ppMap_FILL_FROM_ARRAYS(expected1, keysB, valsB, 2);
  ppMap_FILL_FROM_ARRAYS(expected2, keysA, valsA, 3);
  printf("Test 1.3: swap two non-empty maps\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_swap((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keysB, valsB, 2, &errors, "map1 gets second content");
  check_map_int_content((ppMap*)&map2, keysA, valsA, 3, &errors, "map2 gets first content");
  printf("\n-------------------------------------------\n\n");

  // 2. MOVE
  printf("MOVE\n\n");

  // 2.1 move из непустого в пустой
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysMove[] = {100,200};
  int valsMove[] = {1000,2000};
  ppMap_FILL_FROM_ARRAYS(map2, keysMove, valsMove, 2);
  ppMap_FILL_FROM_ARRAYS(expected1, keysMove, valsMove, 2);
  printf("Test 2.1: move from non-empty to empty\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_move((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keysMove, valsMove, 2, &errors, "map1 gets content");
  check_map_int_content((ppMap*)&map2, NULL, NULL, 0, &errors, "map2 becomes empty after move");
  printf("\n");

  // 2.2 move из непустого в непустой
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysOld[] = {1,2};
  int valsOld[] = {10,20};
  int keysNew[] = {7,8,9};
  int valsNew[] = {70,80,90};
  ppMap_FILL_FROM_ARRAYS(map1, keysOld, valsOld, 2);
  ppMap_FILL_FROM_ARRAYS(map2, keysNew, valsNew, 3);
  ppMap_FILL_FROM_ARRAYS(expected1, keysNew, valsNew, 3);
  printf("Test 2.2: move from non-empty to non-empty (overwrites)\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_move((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keysNew, valsNew, 3, &errors, "map1 gets new content");
  check_map_int_content((ppMap*)&map2, NULL, NULL, 0, &errors, "map2 becomes empty");
  printf("\n-------------------------------------------\n\n");

  // 3. COPY
  printf("COPY\n\n");

  // 3.1 copy из пустого в непустой
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysNotEmpty[] = {11,22};
  int valsNotEmpty[] = {110,220};
  ppMap_FILL_FROM_ARRAYS(map1, keysNotEmpty, valsNotEmpty, 2);
  // expected1 – пустой
  // expected2 остаётся пустым
  printf("Test 3.1: copy from empty to non-empty (clears target)\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_copy((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, NULL, NULL, 0, &errors, "map1 becomes empty");
  check_map_int_content((ppMap*)&map2, NULL, NULL, 0, &errors, "map2 remains empty");
  printf("\n");

  // 3.2 copy из непустого в пустой
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysSrc[] = {100,200,300};
  int valsSrc[] = {1000,2000,3000};
  ppMap_FILL_FROM_ARRAYS(map2, keysSrc, valsSrc, 3);
  ppMap_FILL_FROM_ARRAYS(expected1, keysSrc, valsSrc, 3);
  ppMap_FILL_FROM_ARRAYS(expected2, keysSrc, valsSrc, 3); // исходник не меняется
  printf("Test 3.2: copy from non-empty to empty\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_copy((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keysSrc, valsSrc, 3, &errors, "map1 gets copy");
  check_map_int_content((ppMap*)&map2, keysSrc, valsSrc, 3, &errors, "map2 unchanged");
  // Убедимся, что map1 и map2 независимы – изменим map1 и проверим map2
  ppMap_INSERT(map1, 999, 9999);
  check_map_int_content((ppMap*)&map2, keysSrc, valsSrc, 3, &errors, "map2 unchanged after modifying map1");
  printf("\n");

  // 3.3 copy из непустого в непустой (замена)
  ppMap_CLEAR(map1); ppMap_CLEAR(map2);
  ppMap_CLEAR(expected1); ppMap_CLEAR(expected2);
  int keysDst[] = {5,6};
  int valsDst[] = {50,60};
  int keysSrc2[] = {7,8,9};
  int valsSrc2[] = {70,80,90};
  ppMap_FILL_FROM_ARRAYS(map1, keysDst, valsDst, 2);
  ppMap_FILL_FROM_ARRAYS(map2, keysSrc2, valsSrc2, 3);
  ppMap_FILL_FROM_ARRAYS(expected1, keysSrc2, valsSrc2, 3);
  ppMap_FILL_FROM_ARRAYS(expected2, keysSrc2, valsSrc2, 3);
  printf("Test 3.3: copy from non-empty to non-empty (replaces)\n");
  print_2_maps((ppMap*)&map1, (ppMap*)&map2);
  ppMap_copy((ppMap*)&map1, (ppMap*)&map2);
  check_map_int_content((ppMap*)&map1, keysSrc2, valsSrc2, 3, &errors, "map1 replaced by copy");
  check_map_int_content((ppMap*)&map2, keysSrc2, valsSrc2, 3, &errors, "map2 unchanged");
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}