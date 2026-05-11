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

// Прямые итераторы
void ppContainer_begin<ppContainer* c, ppContainerIterator* it>();
void ppContainer_end<ppContainer* c, ppContainerIterator* it>();
_Bool ppContainerIterator_next<ppContainerIterator* it>();
_Bool ppContainerIterator_prev<ppContainerIterator* it>();
_Bool ppContainerIterator_get_value<ppContainerIterator* it>();
void ppContainerIterator_free<ppContainerIterator* it>();

// Обратные итераторы
void ppContainer_rbegin<ppContainer* c, ppContainerRIterator* rit>();
void ppContainer_rend<ppContainer* c, ppContainerRIterator* rit>();
_Bool ppContainerRIterator_next<ppContainerRIterator* rit>();
_Bool ppContainerRIterator_prev<ppContainerRIterator* rit>();
_Bool ppContainerRIterator_get_value<ppContainerRIterator* rit>();
void ppContainerRIterator_free<ppContainerRIterator* rit>();

// Обход всех элементов контейнера с вызовом callback(value)
void ppContainer_for_each<ppContainer* c>(void (*callback)(void*));

#endif // __ppcontainer_interface__