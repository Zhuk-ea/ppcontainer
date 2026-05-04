// test-pp-list-replace.c - тестирование функции replace итераторов обобщенного списка ppList
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>; // Целочисленная специализация списка
ppListIterator+<int;>; // Целочисленная специализация итератора
ppListRIterator+<int;>; // Целочисленная специализация обратного итератора

//------------------------------------------------------------------------------
// Обработчик специализации, обеспечивающий вывод целочисленного элемента
// Выводится текущий элемент списка с предварительным переводом
// в область специализации
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}

//==============================================================================
// Тестовая функция
//==============================================================================


//------------------------------------------------------------------------------
int main(void) {

  ppList_VAR(int, l_int);

  printf("\n -------------------------------------------\n\n");
  //Вывод параметров настройки l_int
  printf("l_int.(foundation_size = %u, foundation_addr = %p, size = %u)\n",
        l_int.foundation_size, l_int.foundation_addr, l_int.size);

  for (int i = 0; i > -10; --i) {
    ppList_PUSH_BACK(l_int, i)
  }

  printf("l_int: ");
  ppList_print2(stdout, (ppList*)&l_int);
  printf("\n -------------------------------------------\n\n");

  ppListIterator_VAR(int, iter);
  ppList_begin((ppList*)&l_int, (ppListIterator*)&iter);
  int val = 0; 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("iter_val: %i\n", val);
  printf("iter.replace(10)\n");
  ppListIterator_REPLACE(iter, 10);
  ppListIterator_GET_VAL(val, iter)
  printf("iter_val: %i\n", val);
  printf("l_int: ");
  ppList_print2(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");


  return 0;
} // end main

