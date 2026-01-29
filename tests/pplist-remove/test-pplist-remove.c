// test-pplist-remove.c - тестирование функции remove обобщенного списка ppList
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
  int val;


  int arr[] = {1, 2, 1, 4, 3, 5, 6, 7, 1, 3};

  for (int i = 0; i < 10; ++i) {
    ppList_PUSH_BACK(l_int, arr[i])
  }


  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  printf("l_int.remove(1)\n");
  l_int.@ = 1;
  ppList_remove((ppList*)&l_int);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  printf("l_int.remove(3)\n");
  l_int.@ = 3;
  ppList_remove((ppList*)&l_int);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  printf("l_int.remove(0)\n");
  l_int.@ = 0;
  ppList_remove((ppList*)&l_int);
  printf("l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  return 0;
} // end main

