#include <stdio.h>
#include "pplist.h"


ppList+<int;>; // Целочисленная специализация списка

//------------------------------------------------------------------------------
// Обработчик специализации, обеспечивающий вывод целочисленного элемента
// Выводится текущий элемент списка с предварительным переводом
// в область специализации
void ppList_element_print<ppList.int* l>(FILE* f) {//, int index) {
  // ppList_index((ppList*)l, index);
  fprintf(f, "%d\n", l->@);
}


int main(void) {

  ppList_VAR(int, l_int);

  for (int i = 0; i > -10; --i) {
    ppList_PUSH_BACK(l_int, i)
  }

  struct ppListIterator* iter = ppList_begin((ppList*)&l_int);

  (iter->list).@ = 10;
  

  return 0;
} // end main

