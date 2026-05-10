#ifndef TEST_PPLIST_COMMON_H
#define TEST_PPLIST_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pplist.h"

// Печать списка
static inline void print_list(ppList* l, const char* name) {
  printf("%s: ", name);
  ppList_print2(stdout, l);
}

// Печать двух списков
static inline void print_2_lists(ppList* l1, ppList* l2) {
  printf("l1: ");
  ppList_print2(stdout, l1);
  printf("l2: ");
  ppList_print2(stdout, l2);
}

// Проверка условия
static inline void check_condition(int condition, const char* msg, int* errors) {
  if (condition)
    printf("Correct | %s\n", msg);
  else {
  printf("Incorrect | %s\n", msg);
    (*errors)++;
  }
}

// Сравнение списка с ожидаемым
static inline void check_list(ppList* l, ppList* expected, const char* name, int* errors) {
  if (ppList_is_equal(l, expected, sizeof(int))) {
    printf("Correct | %s: ", name);
  } else {
    printf("Incorrect | %s: ", name);
    (*errors)++;
  }
  ppList_print2(stdout, l);
}

// Сравнение списков с ожидаемым 
void check_lists(ppList* l, ppList* anw, int* errors) {
  if (ppList_is_equal(l, anw, sizeof(int))) {
    printf("Correct | l: ");
  } else {
    printf("Incorrect | l: ");
    (*errors)++;
  }
  ppList_print2(stdout, l);
}


#endif // TEST_PPLIST_COMMON_H