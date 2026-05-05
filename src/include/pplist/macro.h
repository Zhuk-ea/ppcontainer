#ifndef __pplist_macro__
#define __pplist_macro__
// macro.h
// Заголовочный файл, обеспечивающий полный интрефейс к возможностям
// процедурно-параметрического списка

//==============================================================================
// Препроцессорные определения, служащие оберткой, расширяющей функциональность.
//==============================================================================

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppList_VAR(foundation_type, list_name)      \
struct ppList.foundation_type list_name;          \
list_name.foundation_size = sizeof(list_name.@);  \
list_name.foundation_addr = &(list_name.@);       \
list_name.size = 0;                                 \
list_name.head = NULL;                             \
list_name.tail = NULL;                             \
list_name.current = NULL;

//------------------------------------------------------------------------------
// Макрос, используемый для занесения значения в хвост списка.
// Обертывает функцию ppList_push_back и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppList_PUSH_BACK(list_name, value) \
list_name.@ = (value); ppList_push_back((ppList*)&list_name);

// Макрос, используемый для занесения значения в голову списка.
// Обертывает функцию ppList_push_front и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppList_PUSH_FRONT(list_name, value) \
list_name.@ = (value); ppList_push_front((ppList*)&list_name);

// Макрос, используемый для занесения значения после текущего элемента
// Обертывает функцию ppList_push_after_current и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppList_PUSH_AFTER_CURRENT(list_name, value) \
list_name.@ = (value); ppList_push_after_current((ppList*)&list_name);

// Макрос, используемый для занесения значения перед текущим элементом
// Обертывает функцию ppList_push_before_current и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppList_PUSH_BEFORE_CURRENT(list_name, value) \
list_name.@ = (value); ppList_push_before_current((ppList*)&list_name);


// Макрос, используемый для замены значения текущего элемента
// Обертывает функцию ppList_replace_current и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppList_REPLACE_CURRENT(list_name, value) \
list_name.@ = (value); ppList_replace_cerrunt((ppList*)&list_name);


//------------------------------------------------------------------------------
// Макрос для занесения первого элемента списка в указанную переменную
#define ppList_GET_FRONT_VAL(destination, list_name) \
ppList_front((ppList*)&list_name); destination = list_name.@;

//------------------------------------------------------------------------------
// Макрос для занесения последнего элемента списка в указанную переменную
#define ppList_GET_BACK_VAL(destination, list_name) \
ppList_back((ppList*)&list_name); destination = list_name.@;

//------------------------------------------------------------------------------
// Макрос для занесения текущего элемента списка в указанную переменную
#define ppList_GET_CURRENT_VAL(destination, list_name) \
ppList_current((ppList*)&list_name); destination = list_name.@;

// Макрос для занесения значения из элемента на который указывает итератор(или обратный итератор) в указанную переменную
#define ppListIterator_GET_VAL(destination, iterator_name) \
memcpy(&destination, iterator_name.node->data, (size_t)iterator_name.list->foundation_size);

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppListIterator_VAR(foundation_type, iterator_name)      \
struct ppListIterator.foundation_type iterator_name;          \

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppListRIterator_VAR(foundation_type, riterator_name)      \
struct ppListRIterator.foundation_type riterator_name;          \


// Макрос, используемый для занесения значения перед элементом на который ссылается итератор
// Обертывает функцию ppListIterator_insert_before и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppListIterator_INSERT_BEFORE(iterator_name, value) \
iterator_name.@ = (value); memcpy(iterator_name.list->foundation_addr, &(iterator_name.@), (size_t)iterator_name.list->foundation_size); ppListIterator_insert_before((ppListIterator*)&iterator_name);

// Макрос, используемый для занесения значения перед элементом на который ссылается итератор
// Обертывает функцию ppListIterator_insert_after и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppListIterator_INSERT_AFTER(iterator_name, value) \
iterator_name.@ = (value); memcpy(iterator_name.list->foundation_addr, &(iterator_name.@), (size_t)iterator_name.list->foundation_size); ppListIterator_insert_after((ppListIterator*)&iterator_name);


// Макрос, используемый для изменения значения узла на который указавает итератор
// Обертывает функцию ppListIterator_replace и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppListIterator_REPLACE(iterator_name, value) \
iterator_name.@ = (value); memcpy(iterator_name.list->foundation_addr, &(iterator_name.@), (size_t)iterator_name.list->foundation_size); ppListIterator_replace((ppListIterator*)&iterator_name);

// Макрос, используемый для объединения двух списков
// Обертывает функцию ppList_merge
#define ppList_MERGE(dest_name, src_name, cmp_name) \
ppList_merge((ppList*)&dest_name, (ppList*)&src_name, cmp_name);

// Макрос, используемый для объединения диапазонов из двух списков
// Обертывает функцию ppList_merge_ranges
#define ppListIterator_MERGE_RANGES(dest_begin, dest_end, src_begin, src_end, cmp_name) \
ppListIterator_merge_ranges((ppListIterator*)&dest_begin, (ppListIterator*)&dest_end, (ppListIterator*)&src_begin, (ppListIterator*)&src_end, cmp_name);

// Макрос, используемый для перемещения итератора на один узел вперёд
// Обертывает функцию ppListIterator_next
#define ppListIterator_NEXT(iterator_name) \
ppListIterator_next((ppListIterator*)&iterator_name);

// Макрос, используемый для перемещения итератора на один узел назад
// Обертывает функцию ppListIterator_prev
#define ppListIterator_PREV(iterator_name) \
ppListIterator_prev((ppListIterator*)&iterator_name);

// Макрос, используемый для получение итератора на начало списка
// Обертывает функцию ppList_begin
#define ppList_BEGIN(list_name, iterator_name) \
ppList_begin((ppList*)&list_name, (ppListIterator*)&iterator_name);

// Макрос, используемый для получение итератора на конец списка
// Обертывает функцию ppList_end
#define ppList_END(list_name, iterator_name) \
ppList_end((ppList*)&list_name, (ppListIterator*)&iterator_name);

// Макрос, используемый для очистки списка
// Обертывает функцию ppList_clear
#define ppList_CLEAR(list_name) \
ppList_clear((ppList*)&list_name);

// Макрос, используемый для вставки диапазона в список после узла на который указывает итератор(списки однотипные)
// Обертывает функцию ppList_splice_after
#define ppList_SPLICE_AFTER(pos, src_begin, src_end) \
ppList_splice_after((ppListIterator*)&pos, (ppListIterator*)&src_begin, (ppListIterator*)&src_end) 


// Макрос, используемый для вставки диапазона в список перед узлом на который указывает итератор(списки однотипные)
// Обертывает функцию ppList_splice_before
#define ppList_SPLICE_BEFORE(pos, src_begin, src_end) \
ppList_splice_before((ppListIterator*)&pos, (ppListIterator*)&src_begin, (ppListIterator*)&src_end) 


// Макрос, используемый для заполнение списка из массива того же типа
#define ppList_FILL_FROM_ARRAY(list, array)           \
do {                                                  \
  size_t _size = sizeof(array) / sizeof((array)[0]);  \
  for (size_t _i = 0; _i < _size; ++_i) {             \
    ppList_PUSH_BACK((list), (array)[_i]);            \
  }                                                   \
} while(0)

#endif // __pplist_macro__
