#ifndef __ppvector_interface__
#define __ppvector_interface__

//==============================================================================
// interface.h
// Интерфейс вектора, используемый при программировании
//==============================================================================

// Начальная инициализация вектора
void ppVector_init(ppVector* v);

// Определение текущего размера вектора
uint32_t ppVector_size(ppVector* v);

// Определение текущей вместимости
uint32_t ppVector_capacity(ppVector* v);

// Резервирование памяти под заданное количество элементов
void ppVector_reserve(ppVector* v, uint32_t new_cap);

// Изменение числа элементов в векторе (size)
// Новые элементы не устанавливаются или вектор обрезается
void ppVector_resize(ppVector* v, uint32_t new_size);

// Освободение памяти до размера size
void ppVector_shrink_to_fit(ppVector* v);

// Занесение в хвост вектора значения, размещенного
// в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppVector_push_back(ppVector* v);

// Неконтролируемый доступ к элементу вектора по индексу.
// Элемент из вектора переносится в основу специализации.
// Оттуда его можно будет забрать, используя знание типа вектора, присваиванием.
void ppVector_index(ppVector* v, uint32_t index);

// Фиксация в основе специализации значения первого элемента вектора
void ppVector_front(ppVector* v);

// Фиксация в основе специализации значения последнего элемента вектора
void ppVector_back(ppVector* v);

// Возврат указателя на текущий вектор элементов в динамической памяти
void* ppVector_data(ppVector* v);

// Вставка осуществляется по целочисленному индексу. Без итераторов
void ppVector_insert_index(ppVector* v, uint32_t index);

// Удаление последнего элемента вектора
void ppVector_pop_back(ppVector* v);

// Удаление из вектора от одного до нескольких элементов
void ppVector_erase(ppVector* v, uint32_t first, uint32_t last);

// Очистка вектора от данных без изменения вместимости
void ppVector_clear(ppVector* v);

// Удаление у вектора динамчески выделенной памяти.
// Переход в начальное состояние
void ppVector_destroy(ppVector* v);

// Обмен содержимым между двумя однотипными векторами
void ppVector_swap(ppVector* v1, ppVector* v2);

// Пересылка данных из одного вектора в другой. Векторы однотипные
void ppVector_move(ppVector* dest, ppVector* src);

// Копирование данных из одного вектора в другой. Векторы однотипные
void ppVector_copy(ppVector* dest, ppVector* src);

// Получение итератора на первый элемент
void ppVector_begin(ppVector* v, ppVectorIterator* it);

// Получение итератора на последний элемент
void ppVector_end(ppVector* v, ppVectorIterator* it);

// Перемещение итератора вперёд (возвращает 1, если успешно, иначе 0)
_Bool ppVectorIterator_next(ppVectorIterator* it);

// Перемещение итератора назад (возвращает 1, если успешно, иначе 0)
_Bool ppVectorIterator_prev(ppVectorIterator* it);

// Получение значения элемента, на который указывает итератор (копирует в специализацию)
_Bool ppVectorIterator_get_value(ppVectorIterator* it);

// Получение обатного итератора на первый элемент с конца
void ppVector_rbegin(ppVector* v, ppVectorRIterator* rit);

// Получение обатного итератора на последний элемент с начала
void ppVector_rend(ppVector* v, ppVectorRIterator* rit);

// Перемещение обатного итератора вперёд(в сторону уменьшения индексов) (возвращает 1, если успешно, иначе 0)
_Bool ppVectorRIterator_next(ppVectorRIterator* rit);

// Перемещение обатного итератора назаз(в сторону увеличения индексов) (возвращает 1, если успешно, иначе 0)
_Bool ppVectorRIterator_prev(ppVectorRIterator* rit);

// Получение значения элемента, на который указывает обратный итератор (копирует в специализацию)
_Bool ppVectorRIterator_get_value(ppVectorRIterator* rit);

#endif // __ppvector_interface__
