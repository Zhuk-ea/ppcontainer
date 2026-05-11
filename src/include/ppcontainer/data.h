#ifndef __ppcontainer_data__
#define __ppcontainer_data__

#include <stdint.h>

// Структура обобщённого контейнера
typedef struct ppContainer {
  uint32_t  foundation_size;    // размер основы специализации
  void*     foundation_addr;    // адрес основы специализации
}<> ppContainer;

// Обобщённый прямой итератор
typedef struct ppContainerIterator {
  struct ppContainer* container;  // указатель на контейнер, с которым связан
  void* internal_iter;            // указатель на конкретный итератор (ppListIterator, ppVectorIterator, ppMapIterator)
}<> ppContainerIterator;

// Обобщённый обратный итератор
typedef struct ppContainerRIterator {
  struct ppContainer* container;
  void* internal_riter;
}<> ppContainerRIterator;

#endif // __ppcontainer_data__