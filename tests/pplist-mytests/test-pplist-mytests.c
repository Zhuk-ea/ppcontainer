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

  printf("Print empty l_int:\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");


  // Занесение значения в конец пустого списка
  ppList_PUSH_BACK(l_int, 1);

  printf("l_int after push_back(1):\n");
  ppList_print(stdout, (ppList*)&l_int);

  // Занесение значения в начало непустого списка
  ppList_PUSH_FRONT(l_int, 2);

  printf("\n -------------------------------------------\n\n");

  printf("l_int after push_front(2):\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");


  // Получение и вывод первого элемента списка
  int front_value; ppList_GET_FRONT_VAL(front_value, l_int)
  printf("FRONT element = %d\n", front_value);

  // Получение и вывод первого элемента списка
  int back_value; ppList_GET_BACK_VAL(back_value, l_int)
  printf("BACK element = %d\n", back_value);

  // Получение и вывод текущего элемента списка через макрос
  int current_value; ppList_GET_CURRENT_VAL(current_value, l_int)
  printf("CURRENT element = %d\n", current_value);

  printf("\n -------------------------------------------\n\n");
  
  ppList_PUSH_AFTER_CURRENT(l_int, 3);
  ppList_PUSH_BEFORE_CURRENT(l_int, 4);
  printf("l_int after push_after_current(3) and push_before_current(4):\n");

  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");


  // Удаление последнего элемента списка
  ppList_pop_back((ppList*)&l_int);
  printf("l_int after pop_back():\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  // Удаление первого элемента списка
  ppList_pop_front((ppList*)&l_int);
  printf("l_int after pop_front():\n");
  ppList_print(stdout, (ppList*)&l_int);

  printf("\n -------------------------------------------\n\n");

  return 0;
} // end main

