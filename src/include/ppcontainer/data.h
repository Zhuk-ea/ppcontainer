#ifndef __ppcontainer_data__
#define __ppcontainer_data__

#include <stdint.h>

// Структура обобщённого контейнера
typedef struct ppContainer {
  uint32_t  foundation_size;    // размер основы специализации
  void*     foundation_addr;    // адрес основы специализации
}<> ppContainer;

#endif // __ppcontainer_data__