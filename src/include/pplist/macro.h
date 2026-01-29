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


#endif // __pplist_macro__
