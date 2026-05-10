#include <stdio.h>
#include <stdlib.h>
#include "ppcontainer.h"

// --------------------------------------------------------------------
// Реализация обобщённых функций (заглушек)
//--------------------------------------------------------------------

uint32_t ppContainer_size<ppContainer* c>() {
  fprintf(stderr, "Error: no specialization for ppContainer_size\n");
  exit(1);
}

void ppContainer_print<ppContainer* c>(FILE* f) {
  fprintf(stderr, "Error: no specialization for ppContainer_print\n");
  exit(1);
}

_Bool ppContainer_empty<ppContainer* c>() {
  fprintf(stderr, "Error: no specialization for ppContainer_empty\n");
  exit(1);
}

void ppContainer_clear<ppContainer* c>() {
  fprintf(stderr, "Error: no specialization for ppContainer_clear\n");
  exit(1);
}

void ppContainer_copy<ppContainer* dest, ppContainer* src>() {
  fprintf(stderr, "Error: no specialization for ppContainer_copy\n");
  exit(1);
}

void ppContainer_move<ppContainer* dest, ppContainer* src>() {
  fprintf(stderr, "Error: no specialization for ppContainer_move\n");
  exit(1);
}

void ppContainer_swap<ppContainer* a, ppContainer* b>() {
  fprintf(stderr, "Error: no specialization for ppContainer_swap\n");
  exit(1);
}