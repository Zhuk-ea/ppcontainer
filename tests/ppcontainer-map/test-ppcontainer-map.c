// test-ppcontainer-map.c - тестирование ppContainer для отображения int->int
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppcontainer.h"
#include "ppmap.h"

// Специализация для ppMap<int,int>
typedef struct IntPair { int key; int value; } IntPair;
ppMap+<IntPair;>;

int cmp_int(const void* a, const void* b) {
  int ia = *(int*)a, ib = *(int*)b;
  return (ia > ib) - (ia < ib);
}

void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

ppContainer_MAP_SPEC(IntPair, IntMapRef)

void print_int_value(void* value) {
  int v;
  memcpy(&v, value, sizeof(int));
  printf("%d ", v);
}

int main() {
  // 1. Инициализация и заполнение
  printf("\n1. Initialization and filling\n");
  ppMap_VAR(IntPair, my_map, cmp_int);
  for (int i = 1; i <= 5; ++i) ppMap_INSERT(my_map, i, i * 100);
  printf("Original map: ");
  ppMap_print(stdout, (ppMap*)&my_map);
  printf("\n");

  IntMapRef map_ref = { &my_map, 0 };
  ppContainer_VAR(IntMapRef, wrapper);
  wrapper.@ = map_ref;

  // 2. size() и empty()
  printf("\n2. size() and empty()\n");
  printf("ppContainer_size = %u (expected 5)\n", ppContainer_size<&wrapper>());
  printf("ppContainer_empty = %d (expected 0)\n", ppContainer_empty<&wrapper>());

  // 3. print()
  printf("\n3. ppContainer_print\n");
  printf("Container contents: ");
  ppContainer_print<&wrapper>(stdout);
  printf("\n");

  // 4. clear()
  printf("\n4. clear()\n");
  ppContainer_clear<&wrapper>();
  printf("After clear: empty = %d, size = %u\n", ppContainer_empty<&wrapper>(), ppContainer_size<&wrapper>());

  // Восстановление map для дальнейших тестов
  for (int i = 1; i <= 3; ++i) ppMap_INSERT(my_map, i, i * 100);
  ppMap_VAR(IntPair, other_map, cmp_int);
  for (int i = 1; i <= 3; ++i) ppMap_INSERT(other_map, i, i * 1000);

  IntMapRef other_ref = { &other_map, 0 };
  ppContainer_VAR(IntMapRef, other_wrapper);
  other_wrapper.@ = other_ref;

  // 5. swap
  printf("\n5. swap()\n");
  printf("Before swap:\n C1: "); ppContainer_print<&wrapper>(stdout); printf("\n C2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");
  ppContainer_swap<&wrapper, &other_wrapper>();
  printf("After swap:\n C1: "); ppContainer_print<&wrapper>(stdout); printf("\n C2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");

  // 6. copy
  printf("\n6. copy()\n");
  ppContainer_clear<&wrapper>();
  ppContainer_copy<&wrapper, &other_wrapper>();
  printf("After copy from C2:\n C1: "); ppContainer_print<&wrapper>(stdout); printf("\n C2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");

  // 7. move
  printf("\n7. move()\n");
  ppContainer_clear<&wrapper>();
  ppContainer_move<&wrapper, &other_wrapper>();
  printf("After move:\n C1: "); ppContainer_print<&wrapper>(stdout); printf("\n C2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");

  // 8. for_each (выводит значения, а не ключи)
  printf("\n8. for_each() on C1 (values only)\n");
  printf("C1 values: ");
  ppContainer_for_each<&wrapper>(print_int_value);
  printf("\n");

  // Очистка
  ppMap_clear((ppMap*)&my_map);
  ppMap_clear((ppMap*)&other_map);
  printf("\nAll tests completed.\n");
  return 0;
}