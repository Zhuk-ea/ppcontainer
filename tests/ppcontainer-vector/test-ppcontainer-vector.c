// test-ppcontainer-vector.c - тестирование ppContainer для вектора целых чисел
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppcontainer.h"
#include "ppvector.h"

// Специализация для ppVector<int>
ppVector+<int;>;

void ppVector_element_print<ppVector.int* v>(FILE* f) {
  fprintf(f, "%d ", v->@);
}

ppContainer_VECTOR_SPEC(int, IntVectorRef)

void print_int(void* value) {
  int v;
  memcpy(&v, value, sizeof(int));
  printf("%d ", v);
}

int main() {
  // 1. Инициализация и заполнение
  printf("\n1. Initialization and filling\n");
  ppVector_VAR(int, my_vec);
  for (int i = 1; i <= 5; ++i) {
    ppVector_PUSH_BACK(my_vec, i * 10);
  }
  printf("Original vector: ");
  ppVector_print(stdout, (ppVector*)&my_vec);
  printf("\n");

  IntVectorRef vec_ref = { &my_vec, 0 };
  ppContainer_VAR(IntVectorRef, wrapper);
  wrapper.@ = vec_ref;

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

  // Восстановление вектора для дальнейших тестов
  for (int i = 1; i <= 3; ++i) ppVector_PUSH_BACK(my_vec, i * 100);
  ppVector_VAR(int, other_vec);
  for (int i = 1; i <= 3; ++i) ppVector_PUSH_BACK(other_vec, i * 1000);

  IntVectorRef other_ref = { &other_vec, 0 };
  ppContainer_VAR(IntVectorRef, other_wrapper);
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

  // 8. for_each
  printf("\n8. for_each() on C1\n");
  printf("C1 contents: ");
  ppContainer_for_each<&wrapper>(print_int);
  printf("\n");

  // Очистка
  ppVector_destroy((ppVector*)&my_vec);
  ppVector_destroy((ppVector*)&other_vec);
  printf("\nAll tests completed.\n");
  return 0;
}