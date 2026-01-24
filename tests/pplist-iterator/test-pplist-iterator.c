// test-pp-list-mytests.c - тестирование обобщенного списка ppList
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>; // Целочисленная специализация списка

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

  struct ppListIterator* iter = ppList_begin((ppList*)&l_int);
  int val; 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("next(iter)\n");
  ppListIterator_next(iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("prev(iter)\n");
  ppListIterator_prev(iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");
  
  struct ppListRIterator* riter = ppList_rbegin((ppList*)&l_int);
  printf("riter = l_int.rbegin()\n");
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("prev(riter)\n");
  ppListRIterator_prev(riter);
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("next(riter)\n");
  ppListRIterator_next(riter);
  ppListIterator_GET_VAL(val, riter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);
  printf("iter\n");
  ppListIterator_next(iter); ppListIterator_next(iter); ppListIterator_next(iter);
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");

  // printf("insert_before(iter, 10):\n");
  // ppListIterator_INSERT_BEFORE(iter, 10);

  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);



  



  return 0;
} // end main

