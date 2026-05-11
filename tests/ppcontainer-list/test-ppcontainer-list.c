// test-ppcontainer-list.c - тестирование ppContainer для списка целых чисел
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppcontainer.h"
#include "pplist.h"

// Специализация для ppList<int>
ppList+<int;>;

void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}

ppContainer_LIST_SPEC(int, IntListRef)

void print_int(void* value) {
  int v;
  memcpy(&v, value, sizeof(int));
  printf("%d ", v);
}

int main() {
  // 1. Инициализация и заполнение
  printf("\n1. Initialization and filling\n");
  ppList_VAR(int, my_list);
  for (int i = 1; i <= 5; ++i) ppList_PUSH_BACK(my_list, i * 10);
  printf("Original list: ");
  ppList_print2(stdout, (ppList*)&my_list);
  printf("\n");

  IntListRef list_ref = { &my_list, 0 };
  ppContainer_VAR(IntListRef, wrapper);
  wrapper.@ = list_ref;

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

  // Восстановление списка для дальнейших тестов
  for (int i = 1; i <= 3; ++i) ppList_PUSH_BACK(my_list, i * 100);
  ppList_VAR(int, other_list);
  for (int i = 1; i <= 3; ++i) ppList_PUSH_BACK(other_list, i * 1000);

  IntListRef other_ref = { &other_list, 0 };
  ppContainer_VAR(IntListRef, other_wrapper);
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
  ppList_clear((ppList*)&my_list);
  ppList_clear((ppList*)&other_list);
  printf("\nAll tests completed.\n");
  return 0;
}