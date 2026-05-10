#ifndef __ppcontainer_interface__
#define __ppcontainer_interface__

#include <stdio.h>
#include "ppcontainer/data.h"

// Обобщённая функция получения размера
uint32_t ppContainer_size<ppContainer* c>();

// Обобщённая функция вывода содержимого
void ppContainer_print<ppContainer* c>(FILE* f);

// Обобщённая функция проверки пуст ли контейнер
_Bool ppContainer_empty<ppContainer* c>();

// Обобщённая функция очистки контейнера
void ppContainer_clear<ppContainer* c>();

// Обобщённая функция копирования контейнера
void ppContainer_copy<ppContainer* dest, ppContainer* src>();

// Обобщённая функция перемещения контейнера
void ppContainer_move<ppContainer* dest, ppContainer* src>();

// Обобщённая функция обмена между контейнерами
void ppContainer_swap<ppContainer* a, ppContainer* b>();

#endif // __ppcontainer_interface__