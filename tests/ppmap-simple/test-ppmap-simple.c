// test-ppmap-simple.c – тест с int значениями (без nested функций)
#include <stdio.h>
#include <string.h>
#include "ppmap.h"

typedef struct IntPair{
  int key;
  int value;
} IntPair;

ppMap+<IntPair;>;

int cmp_int(const void* a, const void* b) {
  int ia = *(int*)a, ib = *(int*)b;
  return (ia > ib) - (ia < ib);
}

void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

void check_condition(int condition, const char* msg, int* errors) {
  if (condition) printf("Correct | %s\n", msg);
  else {
    printf("Incorrect | %s\n", msg);
    (*errors)++;
  }
}

static int traverse_idx;
static int expected_keys[] = {1,2,3};
static int expected_vals[] = {100,200,300};

void traverse_callback(void* key, void* value) {
  if (traverse_idx < 3) {
    int k = *(int*)key;
    int v = *(int*)value;
    if (k == expected_keys[traverse_idx] && v == expected_vals[traverse_idx])
      printf("Correct | traverse step %d\n", traverse_idx+1);
    else
      printf("Incorrect | traverse step %d\n", traverse_idx+1);
    traverse_idx++;
  }
}

int main() {
  int errors = 0;
  ppMap_VAR(IntPair, map, cmp_int);
  ppMap_VAR(IntPair, map2, cmp_int);
  ppMap_VAR(IntPair, empty, cmp_int);
  
  printf(" Test ppMap_insert \n");
  ppMap_INSERT(map, 1, 100);
  ppMap_INSERT(map, 2, 200);
  ppMap_INSERT(map, 3, 300);
  
  ppMap_INSERT(map2, 1, 100);
  ppMap_INSERT(map2, 2, 200);
  ppMap_INSERT(map2, 3, 300);
  
  check_condition(ppMap_is_equal((ppMap*)&map, (ppMap*)&map2), "insert works", &errors);
  
  printf("\nTest ppMap_find\n");
  int val = 0;
  ppMap_FIND(map, 2, val);
  check_condition(val == 200, "find existing key", &errors);
  val = 0;
  ppMap_FIND(map, 99, val);
  check_condition(val == 0, "find non-existing key returns 0", &errors);
  
  printf("\nTest ppMap_erase\n");
  ppMap_ERASE(map, 2);
  val = 0;
  ppMap_FIND(map, 2, val);
  check_condition(val == 0, "erase removes key", &errors);
  int v1 = 0, v3 = 0;
  ppMap_FIND(map, 1, v1);
  ppMap_FIND(map, 3, v3);
  check_condition(v1 == 100 && v3 == 300, "other keys unchanged", &errors);
  
  printf("\nTest ppMap_size / empty\n");
  check_condition(ppMap_size((ppMap*)&map) == 2, "size after erase = 2", &errors);
  check_condition(!ppMap_empty((ppMap*)&map), "not empty", &errors);
  ppMap_clear((ppMap*)&map);
  check_condition(ppMap_size((ppMap*)&map) == 0, "clear size = 0", &errors);
  check_condition(ppMap_empty((ppMap*)&map), "empty after clear", &errors);
  
  printf("\nTest ppMap_traverse\n");
  ppMap_INSERT(map, 2, 200);
  ppMap_INSERT(map, 1, 100);
  ppMap_INSERT(map, 3, 300);
  traverse_idx = 0;
  ppMap_traverse((ppMap*)&map, traverse_callback);
  
  printf("\nTotal errors: %d\n", errors);
  return errors;
}