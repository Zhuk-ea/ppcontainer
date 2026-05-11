// pp-vector.c - определения функций, реализующих операции над обобщенным вектором

// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppvector.h"

//==============================================================================
// Реализация интерфейса обобщенного вектора, используемого при программировании
//==============================================================================

//------------------------------------------------------------------------------
// Начальная инициализация вектора
void ppVector_init(ppVector* v) {
  v->size = 0;
  v->capacity = 0;
  v->vec_memory = NULL;
}

//------------------------------------------------------------------------------
// Определение текущего размера вектора
uint32_t ppVector_size(ppVector* v) {
  return v->size;
}

//------------------------------------------------------------------------------
// Определение текущей вместимости
uint32_t ppVector_capacity(ppVector* v) {
  return v->capacity;
}

//------------------------------------------------------------------------------
// Резервирование памяти под заданное количество элементов
void ppVector_reserve(ppVector* v, uint32_t new_cap) {
  if((v->capacity == 0) && (v->vec_memory == NULL)) { // Начальное состояние
    v->vec_memory = calloc(new_cap, v->foundation_size);
    v->capacity = new_cap;
  } else if ((v->capacity > 0) && (v->capacity < new_cap)) {
    // Вектор уже есть. Допустимо его расширение
    void* tmp_memory_ptr =
          reallocarray(v->vec_memory, new_cap, v->foundation_size);
    // free(v->vec_memory);
    v->vec_memory = tmp_memory_ptr;
    v->capacity = new_cap;
  }
}

//------------------------------------------------------------------------------
// Изменение числа элементов в векторе (size)
// Новые элементы не устанавливаются или вектор обрезается
void ppVector_resize(ppVector* v, uint32_t new_size) {
  uint32_t old_size;
  if(new_size < v->size) { // Просто сбрасывает число элементов, возможно до 0
    v->size = new_size;
    return;
  }
  if((new_size > v->size) && (new_size <= v->capacity)) {
    // Только заполнение нулями до изменененного размера
    old_size = v->size;
    v->size = new_size;
  }
  if(new_size > v->capacity) { // Нужно увеличить вектор до нового размера
    // Фиксация предыдущей вместимости
    old_size = v->size;
    v->size = new_size;
    ppVector_reserve(v, new_size);
  }
  // Заполнение нулями нового пространства под размер данных
  char* first_zero_pos = v->vec_memory + old_size * v->foundation_size;
  char* last_zero_pos = v->vec_memory + new_size * v->foundation_size;
  while(first_zero_pos < last_zero_pos) {
    *first_zero_pos = 0;
    ++first_zero_pos;
  }
}

//------------------------------------------------------------------------------
// Освободение памяти до размера size
void ppVector_shrink_to_fit(ppVector* v) {
  // Выделяется кусок при условии что size < capacity
  if(v->size < v->capacity) {
    v->vec_memory = reallocarray(v->vec_memory, v->size, v->foundation_size);
    v->capacity = v->size;
  }
}

//------------------------------------------------------------------------------
// Занесение в хвост вектора значения, размещенного
// в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppVector_push_back(ppVector* v) {
  if(v->capacity == 0 && v->size == 0) {
    v->capacity = 1;
    // fprintf(stderr, "v->capacity = %u\n", v->capacity);
    v->vec_memory = calloc(1, v->foundation_size);
    // fprintf(stderr, "calloc\n");
    memcpy(v->vec_memory, v->foundation_addr, v->foundation_size);
    // fprintf(stderr, "memcpy\n");
    v->size = 1;
    // fprintf(stderr, "v->size = %u\n", v->size);
  } else if(v->capacity == v->size) {
    v->capacity *= 2;
    v->vec_memory = reallocarray(v->vec_memory, v->capacity, v->foundation_size);
    void* position = v->vec_memory + v->size * v->foundation_size;
    memcpy(position, v->foundation_addr, v->foundation_size);
    ++v->size;
  } else {
    void* position = v->vec_memory + v->size * v->foundation_size;
    memcpy(position, v->foundation_addr, v->foundation_size);
    ++v->size;
  }
}

//------------------------------------------------------------------------------
// Неконтролируемый доступ к элементу вектора по индексу.
// Элемент из вектора переносится в основу специализации.
// Оттуда его можно будет забрать, используя знание типа вектора, присваиванием.
void ppVector_index(ppVector* v, uint32_t index) {
  void* position = v->vec_memory + index * v->foundation_size;
  memcpy(v->foundation_addr, position, v->foundation_size);
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации значения первого элемента вектора
void ppVector_front(ppVector* v) {
  memcpy(v->foundation_addr, v->vec_memory, v->foundation_size);
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации значения последнего элемента вектора
void ppVector_back(ppVector* v) {
  void* position = v->vec_memory + (v->size - 1) * v->foundation_size;
  memcpy(v->foundation_addr, position, v->foundation_size);
}

//------------------------------------------------------------------------------
// Возврат указателя на текущий вектор элементов в динамической памяти
void* ppVector_data(ppVector* v) {
  return v->vec_memory;
}

//------------------------------------------------------------------------------
// Вставка элемента из основы специализации в заданную позицию со сдвигом.
// Вставка осуществляется по целочисленному индексу. Без итераторов.
// Допускается расширение только на 1 элемент при добавлении в конец.
// Вставка по произвольному индексу больше размера элемента не допускается
void ppVector_insert_index(ppVector* v, uint32_t index) {
  if(v->capacity == 0 && v->size == 0) {
    if(index == 0) {
      // При пустом векторе вставка только в нулевую позицию с созданием вектора
      v->capacity = 1;
      v->vec_memory = calloc(1, v->foundation_size);
      memcpy(v->vec_memory, v->foundation_addr, v->foundation_size);
      v->size = 1;
    }
    // При другом значении индекса ничего не делается
  } else if(v->capacity == v->size) { // Вставка ведет к увеличению вектора на 1
    if(index <= v->size) {
      v->capacity *= 2;
      void* new_memory = calloc(v->capacity, v->foundation_size);
      // Вычисление позиции для вставки и ее освобождение сдвигом
      // void* position = v->vec_memory + index * v->foundation_size;
      // void* shif_postion = position + v->foundation_size;
      // Переброс значений  существующее массива в большее пространство
      // Количество элементов до вставки
      uint32_t pre_insert_bytes = index * v->foundation_size;
      uint32_t post_insert_bytes = (v->size - index) * v->foundation_size;
      // В начале копирование элементов до точки вставки
      if(index != 0) { // Копирование первой части только если индекс != 0
        memcpy(new_memory, v->vec_memory, pre_insert_bytes);
      }
      // Вставка элемента из основы
      memcpy(new_memory + pre_insert_bytes, v->foundation_addr, v->foundation_size);
      // Копирование оставшихся элементов
      memcpy(new_memory + (pre_insert_bytes + v->foundation_size),
             v->vec_memory + pre_insert_bytes, post_insert_bytes);
      free(v->vec_memory);
      v->vec_memory = new_memory;
      ++v->size;
    }
    // При большем значении индекса ничего не делается
  } else { // Размерность вектора больше
    if(index <= v->size) {
      // Вычисление позиции для вставки и ее освобождение сдвигом
      void* position = v->vec_memory + index * v->foundation_size;
      void* shif_postion = position + v->foundation_size;
      // Переброс значений  существующее массива в большее пространство
      // Количество элементов до вставки
      uint32_t pre_insert_bytes = index * v->foundation_size;
      uint32_t post_insert_bytes = (v->size - index) * v->foundation_size;
      // Перемещене элементов после вставки
      memmove(v->vec_memory + (pre_insert_bytes + v->foundation_size),
             v->vec_memory + pre_insert_bytes, post_insert_bytes);
      // Вставка элемента из основы
      memcpy(v->vec_memory + pre_insert_bytes, v->foundation_addr, v->foundation_size);
      ++v->size;
    }
  }
}

//------------------------------------------------------------------------------
// Удаление последнего элемента вектора
void ppVector_pop_back(ppVector* v) {
  --(v->size);
}

//------------------------------------------------------------------------------
// Удаление из вектора от одного до нескольких элементов
void ppVector_erase(ppVector* v, uint32_t first, uint32_t last) {
  // Проверка соответствия диапазона
  if((first > last) || (first >= v->size)) {
    // Выход при некорректном соответствии индексов
    return;
  }
  if(last >= v->size) { // Удаляются до конца, но не более
    last = v->size - 1;
  }
  uint32_t number = last - first + 1; // Количество удаляемых элементов
  // Получение первой позиции для удаления
  void* first_erase_position = v->vec_memory + first * v->foundation_size;
  // Получение позиции для переноса оставшихся элементов
  void* first_moving_position = v->vec_memory + (last + 1) * v->foundation_size;
  // Перемещение данных справа на освобождающееся место
  // fprintf(stderr, "[%p, %p, %p]\n",
  //        v->vec_memory, first_erase_position, first_moving_position);
  if(first != v->size - 1) {
    memmove(first_erase_position, first_moving_position,
            (v->size - number) * v->foundation_size);
  }
  v->size -= number;
}

//------------------------------------------------------------------------------
// Очистка вектора от данных без изменения вместимости
void ppVector_clear(ppVector* v) {
  v->size = 0;
  char* tmp = v->foundation_addr;
  for(int i = 0; i < v->foundation_size; ++i) {
    *(tmp + i) = 0;
  }
}

//------------------------------------------------------------------------------
// Удаление у вектора динамчески выделенной памяти.
// Переход в начальное состояние
void ppVector_destroy(ppVector* v) {
  if(v->vec_memory != NULL) {
    free(v->vec_memory);
    v->size = 0;
    v->capacity = 0;
  }
  // Обнуляется основа с векторе (а надо?)
  char* tmp = v->foundation_addr;
  for(int i = 0; i < v->foundation_size; ++i) {
    *(tmp + i) = 0;
  }
}

//------------------------------------------------------------------------------
// Обмен содержимым между двумя однотипными векторами
void ppVector_swap(ppVector* v1, ppVector* v2) {
  // Проверка однотипности векторов
  if(spec_index_cmp(v1, v2) < 1) {
    // Или обобщение или специализации не совпадают
    fprintf(stderr, "Incompatible specializations in swap function\n");
    exit(-1);
  }
  // Или осуществление обмена
  uint32_t tmp = v1->size; v1->size = v2->size; v2->size = tmp;
  tmp = v1->capacity; v1->capacity = v2->capacity; v2->capacity = tmp;
  void* tmp_memory_ptr = v1->vec_memory;
  v1->vec_memory = v2->vec_memory;
  v2->vec_memory = tmp_memory_ptr;
}

//------------------------------------------------------------------------------
// Пересылка данных из одного вектора в другой. Векторы однотипные
void ppVector_move(ppVector* dest, ppVector* src) {
  // Проверка однотипности векторов
  if(spec_index_cmp(dest, src) < 1) {
    // Или обобщение или специализации не совпадают
    fprintf(stderr, "Incompatible specializations in move function\n");
    exit(-1);
  }
  // Или осуществление пересылки
  if(dest->vec_memory != NULL) {  // Нужно убрать выделенный массив, если есть.
    free(dest->vec_memory);
  }
  dest->size = src->size; src->size = 0;
  dest->capacity = src->capacity; src->capacity = 0;
  dest->vec_memory = src->vec_memory;
  src->vec_memory = NULL;
}

//------------------------------------------------------------------------------
// Копирование данных из одного вектора в другой. Векторы однотипные
void ppVector_copy(ppVector* dest, ppVector* src) {
  // Проверка однотипности векторов
  if(spec_index_cmp(dest, src) < 1) {
    // Или обобщение или специализации не совпадают
    fprintf(stderr, "Incompatible specializations in copy function\n");
    exit(-1);
  }
  // Если массив в источнике отсутствует, то обнулить массив и в приемнике
  if(src->vec_memory == NULL) {
    if(dest->vec_memory != NULL) {
      free(dest->vec_memory);
      dest->vec_memory = NULL;
      dest->size = 0;
      dest->capacity = 0;
      return;
    } else { // Тоже пусто. Нечего копировать.
      return;
    }
  }
  // Или осуществление копирования. В начале релокация приемника
  dest->vec_memory = reallocarray(dest->vec_memory,
                                  src->size, dest->foundation_size);
  // Копирование данных из источника в приемник.
  memcpy(dest->vec_memory, src-> vec_memory, src->size * src->foundation_size);
  dest->size = src->size;
  dest->capacity = src->size;
}


//------------------------------------------------------------------------------
// Получение итератора на первый элемент
void ppVector_begin(ppVector* v, ppVectorIterator* it) {
  it->vector = v;
  it->index = 0;
}

//------------------------------------------------------------------------------
// Получение итератора на последний элемент
void ppVector_end(ppVector* v, ppVectorIterator* it) {
  it->vector = v;
  it->index = v->size - 1;
}

//------------------------------------------------------------------------------
// Перемещение итератора вперёд (возвращает 1, если успешно, иначе 0)
_Bool ppVectorIterator_next(ppVectorIterator* it) {
  if (it->index + 1 >= it->vector->size) return 0;
  it->index++;
  return 1;
}

//------------------------------------------------------------------------------
// Перемещение итератора назад (возвращает 1, если успешно, иначе 0)
_Bool ppVectorIterator_prev(ppVectorIterator* it) {
  if (it->index == 0) return 0;
  it->index--;
  return 1;
}

//------------------------------------------------------------------------------
// Получение значения элемента, на который указывает итератор (копирует в специализацию)
_Bool ppVectorIterator_get_value(ppVectorIterator* it) {
  if (it->index >= it->vector->size) return 0;
  void* position = it->vector->vec_memory + it->index * it->vector->foundation_size;
  memcpy(it->vector->foundation_addr, position, it->vector->foundation_size);
  return 1;
}

//------------------------------------------------------------------------------
// Получение обатного итератора на первый элемент с конца
void ppVector_rbegin(ppVector* v, ppVectorRIterator* rit) {
  rit->vector = v;
  rit->index = v->size - 1;
}

//------------------------------------------------------------------------------
// Получение обатного итератора на последний элемент с начала
void ppVector_rend(ppVector* v, ppVectorRIterator* rit) {
  rit->vector = v;
  rit->index = 0;
}

//------------------------------------------------------------------------------
// Перемещение обатного итератора вперёд(в сторону уменьшения индексов) (возвращает 1, если успешно, иначе 0)
_Bool ppVectorRIterator_next(ppVectorRIterator* rit) {
  if (rit->index == 0) return 0;
  rit->index--;
  return 1;
}

//------------------------------------------------------------------------------
// Перемещение обатного итератора назаз(в сторону увеличения индексов) (возвращает 1, если успешно, иначе 0)
_Bool ppVectorRIterator_prev(ppVectorRIterator* rit) {
  if (rit->index + 1 >= rit->vector->size) return 0;
  rit->index++;
  return 1;
}

//------------------------------------------------------------------------------
// Получение значения элемента, на который указывает обратный итератор (копирует в специализацию)
_Bool ppVectorRIterator_get_value(ppVectorRIterator* rit) {
  if (rit->index >= rit->vector->size) return 0;
  void* position = rit->vector->vec_memory + rit->index * rit->vector->foundation_size;
  memcpy(rit->vector->foundation_addr, position, rit->vector->foundation_size);
  return 1;
}