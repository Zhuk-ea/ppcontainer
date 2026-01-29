// test-pp-list-insert.c - тестирование функций "семейства" insert
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

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

  for (int i = 0; i < 5; ++i) {
    ppList_PUSH_BACK(l_int, i)
  }

  ppListIterator_VAR(int, iter);
  ppList_begin((ppList*)&l_int, (ppListIterator*)&iter);

  printf("l_int: \n");
  ppList_print(stdout, (ppList*)&l_int);
  int val = 0; 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");

  ppListIterator_INSERT_BEFORE(iter, 15)

  printf("l_int: \n");
  ppList_print(stdout, (ppList*)&l_int); 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");

  ppListIterator_INSERT_AFTER(iter, 20)

  printf("l_int: \n");
  ppList_print(stdout, (ppList*)&l_int); 
  printf("iter = l_int.begin()\n");
  ppListIterator_GET_VAL(val, iter)
  printf("val: %i\n", val);

  printf("\n -------------------------------------------\n\n");


  return 0;
} // end main

