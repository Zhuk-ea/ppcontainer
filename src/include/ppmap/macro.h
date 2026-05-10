#ifndef __ppmap_macro__
#define __ppmap_macro__

#include <string.h>

//==============================================================================
// Макросы для удобной работы со специализациями map
//==============================================================================

//------------------------------------------------------------------------------
// Создание специализированной переменной map
#define ppMap_VAR(pair_type, map_name, cmp_func)           \
struct ppMap.pair_type map_name;                           \
do {                                                       \
  map_name.key_size = sizeof(((pair_type*)0)->key);        \
  map_name.value_size = sizeof(((pair_type*)0)->value);    \
  map_name.foundation_size = sizeof(pair_type);            \
  map_name.foundation_addr = &(map_name.@);                \
  map_name.size = 0;                                       \
  map_name.root = NULL;                                    \
  map_name.cmp = cmp_func;                                 \
} while(0)

//------------------------------------------------------------------------------
// Вставка пары (ключ, значение) в map
// Обертывает функцию pMap_insert
#define ppMap_INSERT(map_name, key_val, value_val)           \
do {                                                         \
  (map_name).@.key = (key_val);                              \
  (map_name).@.value = (value_val);                          \
  ppMap_insert((ppMap*)&(map_name));                         \
} while(0)

//------------------------------------------------------------------------------
// Поиск значения по ключу.
// Возвращает 1, если ключ найден, иначе 0
// При успехе найденное значение присваивается переменной dest_var,
// при неудаче dest_var присваивается 0 (или значение по умолчанию для типа)
#define ppMap_FIND(map_name, key_val, dest_var)             \
({                                                          \
  (map_name).@.key = (key_val);                             \
  _Bool _found = ppMap_find((ppMap*)&(map_name));           \
  if (_found) {                                             \
    dest_var = (map_name).@.value;                          \
  } else {                                                  \
    dest_var = (__typeof__(dest_var))0;                     \
  }                                                         \
  _found;                                                   \
})

//------------------------------------------------------------------------------
// Получение значения по ключу (предполагается, что ключ существует).
// Если ключ не найден, программа аварийно завершается.
// Обёртывает функцию ppMap_at.
#define ppMap_AT(map_name, key_val)                                \
do {                                                               \
  (map_name).@.key = (key_val);                                    \
  ppMap_at((ppMap*)&(map_name));                                   \
} while(0)


//------------------------------------------------------------------------------
// Удаление элемента по ключу
// Возвращает 1, если элемент был удалён, иначе 0
// Обертывает функцию pMap_erase
#define ppMap_ERASE(map_name, key_val)                             \
((map_name).@.key = (key_val), ppMap_erase((ppMap*)&(map_name)))

//------------------------------------------------------------------------------
// Сравнение двух map на равенство
// Обертывает функцию pMap_is_equal
#define ppMap_IS_EQUAL(map1, map2) ppMap_is_equal((ppMap*)&(map1), (ppMap*)&(map2))

//------------------------------------------------------------------------------
// Очистка map
// Обертывает функцию pMap_clear
#define ppMap_CLEAR(map_name) ppMap_clear((ppMap*)&map_name)

//------------------------------------------------------------------------------
// Заполнение map из двух массивов: ключей и значений одинаковой длины.
#define ppMap_FILL_FROM_ARRAYS(map_name, keys_arr, vals_arr, count)   \
do {                                                                  \
  for (size_t _i = 0; _i < (count); ++_i) {                           \
    (map_name).@.key = (keys_arr)[_i];                                \
    (map_name).@.value = (vals_arr)[_i];                              \
    ppMap_insert((ppMap*)&(map_name));                                \
  }                                                                   \
} while(0)

//------------------------------------------------------------------------------
// Заполнение map из массива пар (структура с полями key и value).
#define ppMap_FILL_FROM_PAIRS(map_name, pairs_arr, count)        \
do {                                                             \
  for (size_t _i = 0; _i < (count); ++_i) {                      \
    (map_name).@ = (pairs_arr)[_i];                              \
    ppMap_insert((ppMap*)&(map_name));                           \
  }                                                              \
} while(0)

//------------------------------------------------------------------------------
// Заполнение map из одномерного массива, где ключи и значения чередуются.
#define ppMap_FILL_FROM_INTERLEAVED(map_name, arr, count_pairs)     \
do {                                                                \
  for (size_t _i = 0; _i < (count_pairs); ++_i) {                   \
    (map_name).@.key = (arr)[2 * _i];                               \
    (map_name).@.value = (arr)[2 * _i + 1];                         \
    ppMap_insert((ppMap*)&(map_name));                              \
  }                                                                 \
} while(0)

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppMapIterator_VAR(foundation_type, iterator_name) \
struct ppMapIterator.foundation_type iterator_name

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppMapRIterator_VAR(foundation_type, iterator_name) \
struct ppMapRIterator.foundation_type iterator_name

//------------------------------------------------------------------------------
// Получение итератора на первый элемент (минимальный ключ)
// Обертывает функцию ppMap_begin
#define ppMap_BEGIN(map_name, iterator_name) \
ppMap_begin((ppMap*)&(map_name), (ppMapIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Получение итератора на последний элемент (максимальный ключ)
// Обертывает функцию ppMap_end
#define ppMap_END(map_name, iterator_name) \
ppMap_end((ppMap*)&(map_name), (ppMapIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Получение обратного итератора на последний элемент (максимальный ключ)
// Обертывает функцию ppMap_rbegin
#define ppMap_RBEGIN(map_name, iterator_name) \
ppMap_rbegin((ppMap*)&(map_name), (ppMapRIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Получение обратного итератора на первый элемент (минимальный ключ)
// Обертывает функцию ppMap_rend
#define ppMap_REND(map_name, iterator_name) \
ppMap_rend((ppMap*)&(map_name), (ppMapRIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Переход к следующему элементу (прямой итератор)
// Обертывает функцию ppMapIterator_next
#define ppMapIterator_NEXT(iterator_name) \
ppMapIterator_next((ppMapIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Переход к предыдущему элементу (прямой итератор)
// Обертывает функцию ppMapIterator_prev
#define ppMapIterator_PREV(iterator_name) \
ppMapIterator_prev((ppMapIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Переход к следующему элементу для обратного итератора (к меньшим ключам)
// Обертывает функцию ppMapRIterator_next
#define ppMapRIterator_NEXT(iterator_name) \
ppMapRIterator_next((ppMapRIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Переход к предыдущему элементу для обратного итератора (к большим ключам)
// Обертывает функцию ppMapRIterator_prev
#define ppMapRIterator_PREV(iterator_name) \
ppMapRIterator_prev((ppMapRIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Получение ключа из текущего узла прямого итератора (копирует в переменную)
#define ppMapIterator_GET_KEY(destination, iterator_name)                            \
do {                                                                                 \
  if ((iterator_name).node == NULL) {                                                \
    printf("Error: ppMapIterator_GET_KEY called on NULL iterator\n");                \
    exit(-1);                                                                        \
  }                                                                                  \
  memcpy(&(destination), iterator_name.node->data, iterator_name.map->key_size); \
} while(0)

//------------------------------------------------------------------------------
// Получение значения из текущего узла прямого итератора
#define ppMapIterator_GET_VALUE(destination, iterator_name)                                                            \
do {                                                                                                                   \
  if ((iterator_name).node == NULL) {                                                                                  \
    printf("Error: ppMapIterator_GET_VALUE called on NULL iterator\n");                                                \
    exit(-1);                                                                                                          \
  }                                                                                                                    \
  memcpy(&(destination), (iterator_name).node->data + (iterator_name).map->key_size, (iterator_name).map->value_size); \
} while(0)

//------------------------------------------------------------------------------
// Получение ключа из текущего узла обратного итератора
#define ppMapRIterator_GET_KEY(destination, iterator_name)                            \
do {                                                                                  \
  if ((iterator_name).node == NULL) {                                                 \
    printf("Error: ppMapRIterator_GET_KEY called on NULL iterator\n");                \
    exit(-1);                                                                         \
  }                                                                                   \
  memcpy(&(destination), (iterator_name).node->data, (iterator_name).map->key_size);  \
} while(0)

//------------------------------------------------------------------------------
// Получение значения из текущего узла обратного итератора
#define ppMapRIterator_GET_VALUE(destination, iterator_name)                                                           \
do {                                                                                                                   \
  if ((iterator_name).node == NULL) {                                                                                  \
    printf("Error: ppMapRIterator_GET_VALUE called on NULL iterator\n");                                               \
    exit(-1);                                                                                                          \
  }                                                                                                                    \
  memcpy(&(destination), (iterator_name).node->data + (iterator_name).map->key_size, (iterator_name).map->value_size); \
} while(0)

//------------------------------------------------------------------------------
// Удаление элемента, на который указывает прямой итератор.
// После удаления итератор сдвигается на родителя удалённого узла (или NULL)
// Обертывает функцию ppMapIterator_erase
#define ppMapIterator_ERASE(iterator_name) \
ppMapIterator_erase((ppMapIterator*)&(iterator_name))

//------------------------------------------------------------------------------
// Поиск итератора по ключу (возвращает 1, если найден, иначе 0)
#define ppMap_FIND_ITERATOR(map_name, key_val, iterator_name)                \
({                                                                       \
  (map_name).@.key = (key_val);                                        \
  ppMap_find_iterator((ppMap*)&(map_name), (ppMapIterator*)&(iterator_name)); \
})

//------------------------------------------------------------------------------
// Установка итератора на lower_bound (первый ключ >= key_val)
#define ppMap_LOWER_BOUND(map_name, key_val, iterator_name)                  \
do {                                                                     \
  (map_name).@.key = (key_val);                                        \
  ppMap_lower_bound((ppMap*)&(map_name), (ppMapIterator*)&(iterator_name)); \
} while(0)

//------------------------------------------------------------------------------
// Установка итератора на upper_bound (первый ключ > key_val)
#define ppMap_UPPER_BOUND(map_name, key_val, iterator_name)                  \
do {                                                                     \
  (map_name).@.key = (key_val);                                        \
  ppMap_upper_bound((ppMap*)&(map_name), (ppMapIterator*)&(iterator_name)); \
} while(0)

//------------------------------------------------------------------------------
// Удаление из map диапазона
// Обертывает функцию ppMapIterator_erase_range
#define ppMapIterator_ERASE_RANGE(begin_iter, end_iter) \
ppMapIterator_erase_range((ppMapIterator*)&(begin_iter), (ppMapIterator*)&(end_iter))

#endif // __ppmap_macro__