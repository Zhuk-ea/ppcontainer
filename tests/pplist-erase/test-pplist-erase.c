// test-pplist-erase.c - тестирование функции erase обобщенного списка ppList
#include <stdio.h>
#include "pplist.h"

//==============================================================================
// Все, что сопровождает формируемую специализацию списка
//==============================================================================

ppList+<int;>; // Целочисленная специализация списка
ppListIterator+<int;>; // Целочисленная специализация списка

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
  int val;

  for (int i = 0; i < 10; ++i) {
    ppList_PUSH_BACK(l_int, i)
  }

  ppListIterator_VAR(int, iter)
  ppList_begin((ppList*)&l_int, (ppListIterator*)&iter);

  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);
  ppListIterator_GET_VAL(val, iter)
  printf("iter = l_int.begin()\n");
  printf("iter_val: %i\n", val);

  printf("\n -------------------------------------------\n\n");

  printf("iter.erase()\n");
  ppListIterator_erase((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("iter_val: %i\n", val);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");


  ppList_end((ppList*)&l_int, (ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("iter = l_int.end()\n");
  printf("iter_val: %i\n", val);

  printf("iter.erase()\n");
  ppListIterator_erase((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("iter_val: %i\n", val);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  ppListIterator_prev((ppListIterator*)&iter); ppListIterator_prev((ppListIterator*)&iter); ppListIterator_prev((ppListIterator*)&iter);

  ppListIterator_GET_VAL(val, iter)
  printf("iter.prev(); iter.prev(); iter.prev();\n");
  printf("iter_val: %i\n", val);

  printf("iter.erase()\n");
  ppListIterator_erase((ppListIterator*)&iter);
  ppListIterator_GET_VAL(val, iter)
  printf("iter_val: %i\n", val);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);


  return 0;
} // end main

