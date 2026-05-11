#include <stdio.h>
#include <stdlib.h>
#include "ppcontainer.h"

// --------------------------------------------------------------------
// Реализация обобщённых функций (заглушек)
//--------------------------------------------------------------------

uint32_t ppContainer_size<ppContainer* c>() {
  printf("Error: no specialization for ppContainer_size\n");
  exit(1);
}

void ppContainer_print<ppContainer* c>(FILE* f) {
  printf("Error: no specialization for ppContainer_print\n");
  exit(1);
}

_Bool ppContainer_empty<ppContainer* c>() {
  printf("Error: no specialization for ppContainer_empty\n");
  exit(1);
}

void ppContainer_clear<ppContainer* c>() {
  printf("Error: no specialization for ppContainer_clear\n");
  exit(1);
}

void ppContainer_copy<ppContainer* dest, ppContainer* src>() {
  printf("Error: no specialization for ppContainer_copy\n");
  exit(1);
}

void ppContainer_move<ppContainer* dest, ppContainer* src>() {
  printf("Error: no specialization for ppContainer_move\n");
  exit(1);
}

void ppContainer_swap<ppContainer* a, ppContainer* b>() {
printf("Error: no specialization for ppContainer_swap\n");
exit(1);
}

// Обобщённые заглушки для итераторов (необходимы для линковки)
void ppContainer_begin<ppContainer* c, ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainer_begin\n");
  exit(1);
}
void ppContainer_end<ppContainer* c, ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainer_end\n");
  exit(1);
}
_Bool ppContainerIterator_next<ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainerIterator_next\n");
  exit(1);
}
_Bool ppContainerIterator_prev<ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainerIterator_prev\n");
  exit(1);
}
_Bool ppContainerIterator_get_value<ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainerIterator_get_value\n");
  exit(1);
}
void ppContainerIterator_free<ppContainerIterator* it>() {
  printf("Error: no specialization for ppContainerIterator_free\n");
  exit(1);
}

void ppContainer_rbegin<ppContainer* c, ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainer_rbegin\n");
  exit(1);
}
void ppContainer_rend<ppContainer* c, ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainer_rend\n");
  exit(1);
}
_Bool ppContainerRIterator_next<ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainerRIterator_next\n");
  exit(1);
}
_Bool ppContainerRIterator_prev<ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainerRIterator_prev\n");
  exit(1);
}
_Bool ppContainerRIterator_get_value<ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainerRIterator_get_value\n");
  exit(1);
}
void ppContainerRIterator_free<ppContainerRIterator* rit>() {
  printf("Error: no specialization for ppContainerRIterator_free\n");
  exit(1);
}

void ppContainer_for_each<ppContainer* c>(void (*callback)(void*)) {
  printf("Error: no specialization for ppContainer_for_each\n");
  exit(1);
}