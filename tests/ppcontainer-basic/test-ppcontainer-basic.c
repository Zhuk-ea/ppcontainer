// test-ppcontainer-list.c - testing ppContainer for list (int)
#include <stdio.h>
#include <stdlib.h>
#include "ppcontainer.h"
#include "pplist.h"

//==============================================================================
// Specialization for ppList<int>
//==============================================================================
ppList+<int;>;

void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}

ppContainer_LIST_SPEC(int, IntListRef)

void print_list(ppList* lst, const char* name) {
  printf("%s: ", name);
  ppList_print2(stdout, lst);
  printf("\n");
}


int main() {
  // 1. Initialization and filling
  printf("\n1. Initialization and filling\n");

  ppList_VAR(int, my_list);
  for (int i = 1; i <= 5; ++i) {
    ppList_PUSH_BACK(my_list, i * 10);
  }
  print_list((ppList*)&my_list, "Original list");

  IntListRef list_ref = { &my_list, 0 };
  ppContainer_VAR(IntListRef, wrapper);
  wrapper.@ = list_ref;

  // 2. size() and empty()
  printf("\n2. Checking size() and empty()\n");
  printf("ppContainer_size = %u (expected 5)\n", ppContainer_size<&wrapper>());
  printf("ppContainer_empty = %d (expected 0)\n", ppContainer_empty<&wrapper>());

  // 3. print()
  printf("\n3. Printing contents via ppContainer_print\n");
  printf("Container contents: ");
  ppContainer_print<&wrapper>(stdout);
  printf("\n");

  //4. clear() and empty()
  printf("\n4. Clearing the container (clear)\n");
  ppContainer_clear<&wrapper>();
  printf("After clear:\n");
  printf("ppContainer_empty = %d (expected 1)\n", ppContainer_empty<&wrapper>());
  printf("ppContainer_size = %u (expected 0)\n", ppContainer_size<&wrapper>());

  ppList_PUSH_BACK(my_list, 100);
  ppList_PUSH_BACK(my_list, 200);
  ppList_PUSH_BACK(my_list, 300);
  print_list((ppList*)&my_list, "Refilled list");
  ppList_VAR(int, other_list);
  for (int i = 1; i <= 3; ++i) {
    ppList_PUSH_BACK(other_list, i * 1000);
  }
  print_list((ppList*)&other_list, "Second list (other)");

  IntListRef other_ref = { &other_list, 0 };
  ppContainer_VAR(IntListRef, other_wrapper);
  other_wrapper.@ = other_ref;

  // 5. swap
  printf("\n5. Swapping contents (swap)\n");
  printf("Before swap:\n");
  printf(" Container 1: "); ppContainer_print<&wrapper>(stdout); printf("\n");
  printf(" Container 2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");

  ppContainer_swap<&wrapper, &other_wrapper>();

  printf("After swap:\n");
  printf(" Container 1: "); ppContainer_print<&wrapper>(stdout); printf("\n");
  printf(" Container 2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");

  // 6. copy
  printf("\n6. Copying (copy) from container 2 to container 1\n");
  ppContainer_clear<&wrapper>();
  printf("After clearing container 1: ");
  ppContainer_print<&wrapper>(stdout); printf("\n");

  ppContainer_copy<&wrapper, &other_wrapper>();
  printf("After copy from container 2:\n");
  printf(" Container 1: "); ppContainer_print<&wrapper>(stdout); printf("\n");
  printf(" Container 2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");
  printf("(container 2 should remain unchanged)\n");

  // 7. move
  printf("\n7. Moving (move) from container 2 to container 1\n");
  ppContainer_clear<&wrapper>();
  printf("After clearing container 1: ");
  ppContainer_print<&wrapper>(stdout); printf("\n");

  ppContainer_move<&wrapper, &other_wrapper>();
  printf("After move:\n");
  printf(" Container 1: "); ppContainer_print<&wrapper>(stdout); printf("\n");
  printf(" Container 2: "); ppContainer_print<&other_wrapper>(stdout); printf("\n");
  printf("(container 2 should become empty)\n");

  // Clean
  ppList_clear((ppList*)&my_list);
  ppList_clear((ppList*)&other_list);

  printf("\nAll tests completed.\n");
  return 0;
}