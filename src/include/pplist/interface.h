#ifndef __pplist_interface__
#define __pplist_interface__

//==============================================================================
// interface.h
// Интерфейс списка, используемый при программировании
//==============================================================================

// Начальная инициализация списка
void ppList_init(ppList* l);

// Определение текущего размера списка
uint32_t ppList_size(ppList* l);

// Установка нового значения в существующий текущий элемент списка
// из значения, находящегося в специализации
void ppList_replace_current(ppList* l);

// Занесение в хвост списка значения, размещенного в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppList_push_back(ppList* l);

// Занесение в голову списка значения, размещенного в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppList_push_front(ppList* l);

// Вставка нового узла после текущего
void ppList_push_after_current(ppList* l);

// Вставка нового узла перед текущим
void ppList_push_before_current(ppList* l);

// Смещение указателя текущего элемента на следующий элемент списка
_Bool ppList_next_current(ppList* l);

// Смещение указателя текущего элемента на предыдущий элемент списка
_Bool ppList_prev_current(ppList* l);

// Установка первого узла текущим
void ppList_front_current(ppList* l);

// Установка последнего узла текущим
void ppList_back_current(ppList* l);

// Проверка текущего на первый элемент списка
_Bool ppList_is_head(ppList* l);

// Проверка текущего на последний элемент списка
_Bool ppList_is_tail(ppList* l);

// Фиксация в основе специализации значения первого элемента списка
void ppList_front(ppList* l);

// Фиксация в основе специализации значения последнего элемента списка
void ppList_back(ppList* l);

// Фиксация в основе специализации значения текущего элемента списка
void ppList_current(ppList* l);

// Удаление последнего элемента списка
void ppList_pop_back(ppList* l);

// Удаление первого элемента списка
void ppList_pop_front(ppList* l);

// Удаление текущего элемента списка
void ppList_pop_current(ppList* l);

// Очистка списка от данных
void ppList_clear(ppList* l);

// Обмен содержимым между двумя однотипными списками
void ppList_swap(ppList* l1, ppList* l2);

// Пересылка данных из одного списка в другой. Списки однотипные
void ppList_move(ppList* dest, ppList* src);

// Копирование данных из одного списка в другой. Списки однотипные
void ppList_copy(ppList* dest, ppList* src);

// Получение итератора указывающего на первый элемент
void ppList_begin(ppList* l, ppListIterator* iter) ;

// Получение итератора указывающего на последний элемент
void ppList_end(ppList* l, ppListIterator* iter);

// Получение итератора указывающего на текущий элемент
void ppList_current_iterator(ppList* l, ppListIterator* iter);

// Смещение итератора на один элемент вперёд
void ppListIterator_next(ppListIterator* iter);

// Смещение итератора на один элемент назад
void ppListIterator_prev(ppListIterator* iter);

// Фиксация в основе специализации списка значения элемента на который ссылается итератор
void ppListIterator_get_value(ppListIterator* iter);

// Получение итератора указывающего на первый элемент
void ppList_rbegin(ppList* l, ppListRIterator* iter);

// Получение итератора указывающего на последний элемент
void ppList_rend(ppList* l, ppListRIterator* iter);

// Получение обратного итератора указывающего на текущий элемент
void ppList_current_riterator(ppList* l, ppListRIterator* iter);

// Смещение итератора на один элемент назад
void ppListRIterator_next(ppListRIterator* riter);

// Смещение итератора на один элемент вперёд
void ppListRIterator_prev(ppListRIterator* riter);

// Фиксация в основе специализации списка значения элемента на который ссылается итератор
void ppListRIterator_get_value(ppListRIterator* riter);

// Вставка нового узла(со значением, записанным в основу специализации) после узла, на который указывает итератор
void ppListIterator_insert_after(ppListIterator* iter);

// Вставка нового узла перед текущим
void ppListIterator_insert_before(ppListIterator* iter);

// Удаление из списка элемента на который ссылается итератор, итератор начинает указывать на следующий элемент(если он есть), или предыдущий(если элемент был последним)
void ppListIterator_erase(ppListIterator* iter);

// Удаление из списка всех элементов, равных значению, занесённому в специализацию
void ppList_remove(ppList* l);

#endif // __pplist_interface__
