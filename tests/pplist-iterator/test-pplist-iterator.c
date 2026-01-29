// test-pp-list-iterator.c - тестирование базовых функций итераторов обобщенного списка ppList
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
void ppList_element_print<ppList.int* l>(FILE* f) {//, int index) {
  // ppList_index((ppList*)l, index);
  fprintf(f, "%d\n", l->@);
}

//==============================================================================
// Тестовая функция
//==============================================================================


//------------------------------------------------------------------------------
int main(void) {

  ppList_VAR(int, l_int);

  //Вывод параметров настройки l_int
  printf("l_int.(foundation_size = %u, foundation_addr = %p, size = %u)\n",
        l_int.foundation_size, l_int.foundation_addr, l_int.size);

  printf("\n -------------------------------------------\n\n");

  for (int i = 0; i > -10; --i) {
    ppList_PUSH_BACK(l_int, i)
  }

  ppListIterator_VAR(int, iter);
  ppList_begin((ppList*)&l_int, (ppListIterator*)&iter);
  int val = 0; 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("next(iter)\n");
  ppListIterator_next((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("prev(iter)\n");
  ppListIterator_prev((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");
  
  ppListRIterator_VAR(int, riter);
  ppList_rbegin((ppList*)&l_int, (ppListRIterator*)&riter);
  printf("riter = l_int.rbegin()\n");
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("prev(riter)\n");
  ppListRIterator_prev((ppListRIterator*)&riter);
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("next(riter)\n");
  ppListRIterator_next((ppListRIterator*)&riter);
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);
  printf("iter\n");
  ppListIterator_next((ppListIterator*)&iter); ppListIterator_next((ppListIterator*)&iter); ppListIterator_next((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");

  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);


  return 0;
} // end main

