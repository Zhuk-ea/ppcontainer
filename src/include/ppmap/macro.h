#ifndef __ppmap_macro__
#define __ppmap_macro__

#include <string.h>

//==============================================================================
// Макросы для удобной работы со специализациями map
//==============================================================================

//------------------------------------------------------------------------------
// Создание специализированной переменной map
#define ppMap_VAR(pair_type, map_name)                                      \
    struct ppMap.pair_type map_name;                                        \
    do {                                                                    \
        map_name.key_size = sizeof(((pair_type*)0)->key);                   \
        map_name.value_size = sizeof(((pair_type*)0)->value);               \
        map_name.foundation_size = sizeof(pair_type);                       \
        map_name.foundation_addr = &(map_name.@);                           \
        map_name.size = 0;                                                  \
        map_name.root = NULL;                                               \
        map_name.cmp = NULL;                                                \
    } while(0)

//------------------------------------------------------------------------------
// Вставка пары (ключ, значение) в map
// Обертывает функцию pMap_insert
#define ppMap_INSERT(map_name, key_val, value_val)                          \
    do {                                                                    \
        (map_name).@.key = (key_val);                                       \
        (map_name).@.value = (value_val);                                   \
        ppMap_insert((ppMap*)&(map_name));                                  \
    } while(0)

//------------------------------------------------------------------------------
// Поиск значения по ключу
// (если ключ не найден, присваивается 0)
// Обертывает функцию pMap_find
#define ppMap_FIND(map_name, key_val, dest_var)                             \
    do {                                                                    \
        (map_name).@.key = (key_val);                                       \
        if (ppMap_find((ppMap*)&(map_name))) {                              \
            dest_var = (map_name).@.value;                                  \
        } else {                                                            \
            dest_var = (__typeof__(dest_var))0;                             \
        }                                                                   \
    } while(0)

//------------------------------------------------------------------------------
// Удаление элемента по ключу
// Возвращает 1, если элемент был удалён, иначе 0
// Обертывает функцию pMap_erase
#define ppMap_ERASE(map_name, key_val)                                      \
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
#define ppMap_FILL_FROM_ARRAYS(map_name, keys_arr, vals_arr, count)          \
    do {                                                                     \
        for (size_t _i = 0; _i < (count); ++_i) {                            \
            (map_name).@.key = (keys_arr)[_i];                               \
            (map_name).@.value = (vals_arr)[_i];                             \
            ppMap_insert((ppMap*)&(map_name));                               \
        }                                                                    \
    } while(0)

//------------------------------------------------------------------------------
// Заполнение map из массива пар (структура с полями key и value).
#define ppMap_FILL_FROM_PAIRS(map_name, pairs_arr, count)                    \
    do {                                                                     \
        for (size_t _i = 0; _i < (count); ++_i) {                            \
            (map_name).@ = (pairs_arr)[_i];                                  \
            ppMap_insert((ppMap*)&(map_name));                               \
        }                                                                    \
    } while(0)

//------------------------------------------------------------------------------
// Заполнение map из одномерного массива, где ключи и значения чередуются.
#define ppMap_FILL_FROM_INTERLEAVED(map_name, arr, count_pairs)              \
    do {                                                                     \
        for (size_t _i = 0; _i < (count_pairs); ++_i) {                      \
            (map_name).@.key = (arr)[2 * _i];                                \
            (map_name).@.value = (arr)[2 * _i + 1];                          \
            ppMap_insert((ppMap*)&(map_name));                               \
        }                                                                    \
    } while(0)

#endif // __ppmap_macro__