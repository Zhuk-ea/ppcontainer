#ifndef __ppvector_macro__
#define __ppvector_macro__
// macro.h
// Заголовочный файл, обеспечивающий полный интрефейс к возможностям
// процедурно-параметрического вектора

//==============================================================================
// Препроцессорные определения, служащие оберткой, расширяющей функциональность.
//==============================================================================

//------------------------------------------------------------------------------
// Макроопределение, используемое для формирования специализации по шаблону
// Скрывает дополнительные манипуляции, связанные с установкой
// внутренних параметров
#define ppVector_VAR(foundation_type, vector_name)   \
struct ppVector.foundation_type vector_name;     \
vector_name.foundation_size = sizeof(vector_name.@); \
vector_name.foundation_addr = &(vector_name.@);    \
vector_name.size = 0;                 \
vector_name.capacity = 0;               \
vector_name.vec_memory = NULL;
// struct ppVector.foundation_type vector_name =
// {sizeof(vector_name.@), &(vector_name.@),0,0};

//------------------------------------------------------------------------------
// Макрос, используемый для занесения значения в хвост вектора.
// Обертывает функцию ppVector_push_back и предварительное присваивание
// пересылаемого значения внутренней переменной
#define ppVector_PUSH_BACK(vector_name, value) \
vector_name.@ = (value); ppVector_push_back((ppVector*)&vector_name);

//------------------------------------------------------------------------------
// Макрос, используемый для чтения элемента из вектора в заданную переменну.
// Обертывает функцию ppVector_index и присваивание внутренней переменной
// указанной внешней переменной
#define ppVector_GET_VAL_INDEX(destination, vector_name, index) \
ppVector_index((ppVector*)&vector_name, (index)); destination = vector_name.@;

//------------------------------------------------------------------------------
// Макрос для занесения первого элемента вектора в указанную переменную
#define ppVector_GET_FRONT_VAL(destination, vector_name) \
ppVector_front((ppVector*)&vector_name); destination = vector_name.@;

//------------------------------------------------------------------------------
// Макрос для занесения последнего элемента вектора в указанную переменную
#define ppVector_GET_BACK_VAL(destination, vector_name) \
ppVector_back((ppVector*)&vector_name); destination = vector_name.@;

//------------------------------------------------------------------------------
// Макрос для создания специализированной переменной итератора
#define ppVectorIterator_VAR(elem_type, it_name) \
struct ppVectorIterator.elem_type it_name;

//------------------------------------------------------------------------------
// Макрос для получения значения из итератора в переменную
#define ppVectorIterator_GET_VAL(destination, it_name) \
do { \
  if ((it_name).index >= (it_name).vector->size) { \
    fprintf(stderr, "Error: ppVectorIterator_GET_VAL out of range\n"); \
    exit(-1); \
  } \
  memcpy(&destination, \
    (char*)(it_name).vector->vec_memory + (it_name).index * (it_name).vector->foundation_size, \
    (it_name).vector->foundation_size); \
} while(0)

//------------------------------------------------------------------------------
// Макрос для перемещения итератора вперёд
#define ppVectorIterator_NEXT(it_name) \
ppVectorIterator_next((ppVectorIterator*)&(it_name))

//------------------------------------------------------------------------------
// Макрос для перемещения итератора назад
#define ppVectorIterator_PREV(it_name) \
ppVectorIterator_prev((ppVectorIterator*)&(it_name))

//------------------------------------------------------------------------------
// Макрос для создания специализированной переменной обратного итератора
#define ppVectorRIterator_VAR(elem_type, rit_name) \
struct ppVectorRIterator.elem_type rit_name;

//------------------------------------------------------------------------------
// Макрос для получения значения из обратного итератора в переменную
#define ppVectorRIterator_GET_VAL(destination, rit_name) \
do { \
  if ((rit_name).index >= (rit_name).vector->size) { \
    fprintf(stderr, "Error: ppVectorRIterator_GET_VAL out of range\n"); \
    exit(-1); \
  } \
  memcpy(&destination, \
    (char*)(rit_name).vector->vec_memory + (rit_name).index * (rit_name).vector->foundation_size, \
    (rit_name).vector->foundation_size); \
} while(0)

//------------------------------------------------------------------------------
// Макрос для перемещения обратного итератора вперёд
#define ppVectorRIterator_NEXT(rit_name) \
ppVectorRIterator_next((ppVectorRIterator*)&(rit_name))

//------------------------------------------------------------------------------
// Макрос для перемещения обратного итератора назад
#define ppVectorRIterator_PREV(rit_name) \
ppVectorRIterator_prev((ppVectorRIterator*)&(rit_name))

#endif // __ppvector_macro__
