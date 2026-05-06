// test-pplist-simple-functions.c - тестирование простых функции для списка, которые было решено не разделять на отдельные файлы 
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
void ppList_element_print<ppList.int* l>(FILE* f) {
  fprintf(f, "%d ", l->@);
}


void is_correct(ppList* l, ppList* anw) {
  if (ppList_is_equal(l, anw, sizeof(int))) printf("Correct ");
  else printf("Incorrect ");
}

void print_test_results(ppList* l, ppList* anw) {
    is_correct(l, anw);
    printf("| l: "); 
    ppList_print2(stdout, l);
}

//------------------------------------------------------------------------------
int main(void) {

  ppList_VAR(int, l);
  ppList_VAR(int, anw);

  printf("\n-------------------------------------------\n\n");


  // Тест ppList_empty
  printf("Test ppList_empty (empty list):");
  if (ppList_empty((ppList*)&l)) {
    printf("Correct\n");
  } else {
    printf("Incorrect\n");
  }

  int arr[] = {1,2,3};
  ppList_FILL_FROM_ARRAY(l, arr);

  printf("Test ppList_empty (non-empty list): ");
  if (!ppList_empty((ppList*)&l)) {
    printf("Correct\n");
  } else {
    printf("Incorrect\n");
  }

  printf("\n-------------------------------------------\n\n");

  // Тест ppList_size
  ppList_CLEAR(l);
  printf("Test ppList_size: size = %u (expected 0)\n", ppList_size((ppList*)&l));
  ppList_PUSH_BACK(l, 10);
  printf("After push_back, size = %u (expected 1)\n", ppList_size((ppList*)&l));
  ppList_PUSH_FRONT(l, 20);
  printf("After push_front, size = %u (expected 2)\n", ppList_size((ppList*)&l));
  ppList_clear((ppList*)&l);
  printf("After clear, size = %u (expected 0)\n", ppList_size((ppList*)&l));
  printf("\n-------------------------------------------\n\n");

  // Тест ppList_clear
  ppList_FILL_FROM_ARRAY(l, arr);
  ppList_CLEAR(anw);

  printf("Test ppList_clear: before clear\n");
  printf("l: ");
  ppList_print2(stdout, (ppList*)&l);
  ppList_clear((ppList*)&l);
  printf("After clear:\n");
  print_test_results((ppList*)&l, (ppList*)&anw);

  printf("\n-------------------------------------------\n\n");

  // Тест ppList_replace_current
  ppList_CLEAR(l);
  ppList_CLEAR(anw);
  ppList_PUSH_BACK(l, 5);
  ppList_PUSH_BACK(l, 6); 
  
  // current указывает на 6 (хвост)
  ppList_REPLACE_CURRENT(l, 100);

  ppList_PUSH_BACK(anw, 5);
  ppList_PUSH_BACK(anw, 100);
  printf("Test ppList_replace_current:\n");
  print_test_results((ppList*)&l, (ppList*)&anw);

  int cur_val;
  ppList_GET_CURRENT_VAL(cur_val, l);
  printf("Current value after replace: %d (expected 100)\n", cur_val);

  ppList_CLEAR(l);
  int res =  ppList_replace_current((ppList*)&l);
  printf("Tryinng replace current in empty list. ppList_replace_current result: %d (expected 0 == do nothing)\n", res);


  printf("\n-------------------------------------------\n\n");

  return 0;
}