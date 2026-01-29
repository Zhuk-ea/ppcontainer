#include <stdio.h>
#include "pplist.h"


ppList+<int;>; // Целочисленная специализация списка
ppListIterator+<int;>; // Целочисленная специализация итератора

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
  ppListIterator_VAR(int, iter);

  for (int i = 0; i > -10; --i) {
    ppList_PUSH_BACK(l_int, i)
  }


  ppList_begin((ppList*)&l_int, (ppListIterator*)&iter);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  ppListIterator_INSERT_BEFORE(iter, 50);
  
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  return 0;
} // end main

