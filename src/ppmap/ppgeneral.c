// ppgeneral.c - определения обобщающих функций для ppMap
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmap.h"

//------------------------------------------------------------------------------
// Обобщающая функция вывода элемента отображения.
// Переопределяется для каждой специализации.
void ppMap_element_print<ppMap* m>(FILE* f) {
  fprintf(f, "No specialized print function for ppMap element\n");
  exit(-1);
}

//------------------------------------------------------------------------------
// Структура для передачи данных в callback печати
typedef struct {
  FILE* f;
  ppMap* m;
} PrintData;

//------------------------------------------------------------------------------
// Callback для печати одного узла
static void print_node_callback(void* key, void* value, void* user_data) {
  PrintData* pd = (PrintData*)user_data;
  // Копирование пары (ключ+значение) в основу специализации
  memcpy(pd->m->foundation_addr, key, pd->m->key_size);
  memcpy(pd->m->foundation_addr + pd->m->key_size, value, pd->m->value_size);
  // Вызов специализированной функции вывода
  ppMap_element_print<pd->m>(pd->f);
}

//------------------------------------------------------------------------------
// Функция, осуществляющая вывод всех элементов в порядке возрастания ключей
void ppMap_print(FILE* f, ppMap* m) {
  PrintData pd = { f, m };
  ppMap_traverse_with_data(m, print_node_callback, &pd);
  fprintf(f, "\n");
}