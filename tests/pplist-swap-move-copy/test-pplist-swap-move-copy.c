// test-pp-list-swap-move-copy.c - тестирование функций swap, move, copy обобщенного списка ppList
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

//------------------------------------------------------------------------------
int main(void) {

  ppList_VAR(int, l1);
  ppList_VAR(int, l2);

  //Вывод параметров настройки l1
  printf("l1.(foundation_size = %u, foundation_addr = %p, size = %u)\n",
        l1.foundation_size, l1.foundation_addr, l1.size);

  printf("\n -------------------------------------------\n\n");

  //Вывод параметров настройки l2
  printf("l2.(foundation_size = %u, foundation_addr = %p, size = %u)\n",
        l2.foundation_size, l2.foundation_addr, l2.size);

  printf("\n -------------------------------------------\n\n");

  for (int i = 0; i < 10; ++i) {
    ppList_PUSH_BACK(l1, i);
  }

  printf("l1:\n");
  ppList_print(stdout, (ppList*)&l1);

  printf("\n -------------------------------------------\n\n");

  for (int i = 0; i > -10; --i) {
    ppList_PUSH_BACK(l2, i);
  }

  printf("l2:\n");
  ppList_print(stdout, (ppList*)&l2);

  printf("\n -------------------------------------------\n\n");

  printf("swap(l1, l2)\n");
  ppList_swap((ppList*)&l1, (ppList*)&l2);
  printf("l1:\n");
  ppList_print(stdout, (ppList*)&l1);
  printf("\nl2:\n");
  ppList_print(stdout, (ppList*)&l2);
  printf("\n -------------------------------------------\n\n");

  printf("move(l1, l2)\n");
  ppList_move((ppList*)&l1, (ppList*)&l2);
  printf("l1:\n");
  ppList_print(stdout, (ppList*)&l1);
  printf("\nl2:\n");
  ppList_print(stdout, (ppList*)&l2);
  printf("\n -------------------------------------------\n\n");

  printf("copy(l2, l1)\n");
  ppList_copy((ppList*)&l2, (ppList*)&l1);
  printf("l1:\n");
  ppList_print(stdout, (ppList*)&l1);
  printf("\nl2:\n");
  ppList_print(stdout, (ppList*)&l2);
  printf("\n -------------------------------------------\n\n");


  return 0;
} // end main

