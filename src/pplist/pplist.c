// pplist.c - определения функций, реализующих операции над обобщенным списком

// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pplist.h"

//==============================================================================
// Реализация интерфейса обобщенного списка, используемого при программировании
//==============================================================================

//------------------------------------------------------------------------------
// Начальная инициализация списка
void ppList_init(ppList* l) {
  l->size = 0;
  l->head = NULL;
  l->tail = NULL;
  l->current = NULL;
}

//------------------------------------------------------------------------------
// Определение текущего размера списка
uint32_t ppList_size(ppList* l) {
  return l->size;
}

//------------------------------------------------------------------------------
// Установка нового значения в существующий текущий элемент списка
// из значения, находящегося в специализации
void ppList_replace_current(ppList* l) {
  if(l->current == NULL) {
    printf("Incorrect current value in ppList_replace_current function\n");
    exit(-1);
  }
  // Перенос значения из специализации в текущий узел
  memcpy(l->current->data, l->foundation_addr, l->foundation_size);
}

//------------------------------------------------------------------------------
// Занесение в хвост списка значения, размещенного в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppList_push_back(ppList* l) {
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + l->foundation_size);
  if(node == NULL) {
    printf("Incorrect node creation in ppList_push_back function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, l->foundation_addr, l->foundation_size);
  // Прикрепление созданного узла к концу двунаправленного линейного списка
  if(l->head==NULL) { // Занесение в пустой список
    l->head = node;
    l->tail = node;
    // Формирование пустых концов
    node->next = node->prev = NULL;
  } else { // В противном случае формируемый элемент заносится в хвост списка
    node->next = NULL;
    node->prev = l->tail;
    l->tail->next = node;
    l->tail = node;
  }
  l->current = node;    // добавляемый узел становится текущим
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Занесение в начало списка значения, размещенного в специализированной переменной.
// Предварительно значение должно быть занесено в специализацию
void ppList_push_front(ppList* l) {
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + l->foundation_size);
  if(node == NULL) {
    printf("Incorrect node creation in ppList_push_back function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, l->foundation_addr, l->foundation_size);
  // Прикрепление созданного узла к началу двунаправленного линейного списка
  if(l->head==NULL) { // Занесение в пустой список
    l->head = node;
    l->tail = node;
    // Формирование пустых концов
    node->next = node->prev = NULL;
  } else { // В противном случае формируемый элемент заносится в голову списка
    node->next = l->head;
    node->prev = NULL;
    l->head->prev = node;
    l->head = node;
  }
  l->current = node;    // добавляемый узел становится текущим
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Вставка нового узла после текущего
void ppList_push_after_current(ppList* l) {
  if(l->current == NULL) {
    printf("Incorrect current value in ppList_push_after_current function\n");
    exit(-1);
  }
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + l->foundation_size);
  if(node == NULL) {
    printf("Incorrect node creation in ppList_push_after_current function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, l->foundation_addr, l->foundation_size);
  // Прикрепление созданного узла после текущего
  node->next = l->current->next;
  node->prev = l->current;
  l->current->next = node;
  if(l->tail == l->current) { // Для последнего элемента нужно перемещение
    l->tail = node;
  } else { // связь следующего узла с создаваемым
    node->next->prev = node;
  }
  l->current = node;    // добавляемый узел становится текущим
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Вставка нового узла перед текущим
void ppList_push_before_current(ppList* l) {
  if(l->current == NULL) {
    printf("Incorrect current value in ppList_push_before_current function\n");
    exit(-1);
  }
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + l->foundation_size);
  if(node == NULL) {
    printf("Incorrect node creation in ppList_push_before_current function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, l->foundation_addr, l->foundation_size);
  // Прикрепление созданного узла перед текущим
  node->prev = l->current->prev;
  node->next = l->current;
  l->current->prev = node;
  if(l->head == l->current) { // Для последнего элемента нужно перемещение
    l->head = node;
  } else { // связь предыдущего узла с создаваемым
    node->prev->next = node;
  }
  l->current = node;    // добавляемый узел становится текущим
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Смещение указателя текущего элемента на следующий элемент списка
_Bool ppList_next_current(ppList* l) {
  // Если осуществляется вызов для пустого указателя, то ошибка
  // Поэтому перед вызовом стоит делать проверку на последний элемент.
  if(l->current == l->tail) { // Шаг приводит к ошибки и не делается
    return 0;
  }
  l->current = l->current->next;
  return 1; // Шаг успешно сделан
}

//------------------------------------------------------------------------------
// Смещение указателя текущего элемента на предыдущий элемент списка
_Bool ppList_prev_current(ppList* l) {
  // Если осуществляется вызов для пустого указателя, то ошибка
  // Поэтому перед вызовом стоит делать проверку на первый элемент.
  if(l->current == l->head) { // Шаг приводит к ошибки и не делается
    return 0;
  }
  l->current = l->current->prev;
  return 1; // Шаг успешно сделан
}

//------------------------------------------------------------------------------
// Установка первого узла текущим
void ppList_front_current(ppList* l) {
  l->current = l->head;
}

//------------------------------------------------------------------------------
// Установка последнего узла текущим
void ppList_back_current(ppList* l) {
  l->current = l->tail;
}

//------------------------------------------------------------------------------
// Проверка текущего на первый элемент списка
_Bool ppList_is_head(ppList* l) {
  return l->current == l->head;
}

//------------------------------------------------------------------------------
// Проверка текущего на последний элемент списка
_Bool ppList_is_tail(ppList* l) {
  return l->current == l->tail;
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации значения первого элемента списка
void ppList_front(ppList* l) {
  memcpy(l->foundation_addr, l->head->data, l->foundation_size);
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации значения последнего элемента списка
void ppList_back(ppList* l) {
  memcpy(l->foundation_addr, l->tail->data, l->foundation_size);
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации значения текущего элемента списка
void ppList_current(ppList* l) {
  memcpy(l->foundation_addr, l->current->data, l->foundation_size);
}

//------------------------------------------------------------------------------
// Удаление последнего элемента списка
void ppList_pop_back(ppList* l) {
  if(l->tail == NULL) {
    return;
  }
  if(l->size == 1) {
    l->head = NULL;
  }
  l->current = l->tail->prev;
  free(l->tail);
  l->tail = l->current;
  --(l->size);
}

//------------------------------------------------------------------------------
// Удаление первого элемента списка
void ppList_pop_front(ppList* l) {
  if(l->head == NULL) {
    return;
  }
  if(l->size == 1) {
    l->tail = NULL;
  }
  l->current = l->head->next;
  free(l->head);
  l->head = l->current;
  --(l->size);
}

//------------------------------------------------------------------------------
// Удаление текущего элемента списка
void ppList_pop_current(ppList* l) {
  // if(l->current == NULL) {
  //   return;
  // }
  if(l->current == l->head) {
    ppList_pop_front(l);
  } else if(l->current == l->tail) {
    ppList_pop_back(l);
  } else { // где-то в середине
    l->current->prev->next = l->current->next;
    l->current->next->prev = l->current->prev;
    free(l->current);
    l->current = l->head;
    --(l->size);
  }
}

//------------------------------------------------------------------------------
// Очистка списка от всех узлов
void ppList_clear(ppList* l) {
  while(l->size != 0) {
    ppList_pop_back(l);
  }
}

//------------------------------------------------------------------------------
// Обмен содержимым между двумя однотипными списками
void ppList_swap(ppList* l1, ppList* l2) {
  // Проверка однотипности списоков
  if(spec_index_cmp(l1, l2) < 1) {
  // Или обобщение или специализации не совпадают
    printf("Incompatible specializations in swap function\n");
    exit(-1);
  }
  // Осуществление обмена
  uint32_t tmp = l1->size; l1->size = l2->size; l2->size = tmp;
  struct ppListNode* tmp_node_ptr = l1->current; l1->current = l2->current; l2->current = tmp_node_ptr;
  tmp_node_ptr = l1->head; l1->head = l2->head; l2->head = tmp_node_ptr;
  tmp_node_ptr = l1->tail; l1->tail = l2->tail; l2->tail = tmp_node_ptr;
}

//------------------------------------------------------------------------------
// Пересылка данных из одного списка в другой. Списки однотипные
void ppList_move(ppList* dest, ppList* src) {
  // Проверка однотипности списоков
  if(spec_index_cmp(dest, src) < 1) {
    // Или обобщение или специализации не совпадают
    printf("Incompatible specializations in move function\n");
    exit(-1);
  }
  // Или осуществление пересылки
  // Очистка списка в который идёт перессылка
  ppList_clear(dest);

  dest->size = src->size; src->size = 0;
  dest->current = src->current; src->current = NULL;
  dest->head = src->head; src->head = NULL;
  dest->tail = src->tail; src->tail = NULL;

}

//------------------------------------------------------------------------------
// Копирование данных из одного списка в другой. Списки однотипные
void ppList_copy(ppList* dest, ppList* src) {
  // Проверка однотипности списоков
  if(spec_index_cmp(dest, src) < 1) {
    // Или обобщение или специализации не совпадают
    printf("Incompatible specializations in copy function\n");
    exit(-1);
  }
  // Очистка списка в который идёт копирование
  ppList_clear(dest);
  // Осуществление копирования
  struct ppListNode * now = src->head;
  while(now != NULL) {
    
    // Создание элемента списка под данные размером в основу специализации
    struct ppListNode* node = malloc(sizeof(struct ppListNode) + dest->foundation_size);
    if(node == NULL) {
      printf("Incorrect node creation in ppList_copy function\n");
      exit(-1);
    }
    // Перенос значения узла в узел
    memcpy(node->data, now->data, dest->foundation_size);
    // Прикрепление созданного узла к концу двунаправленного линейного списка
    if(dest->head==NULL) { // Занесение в пустой список
      dest->head = node;
      dest->tail = node;
      // Формирование пустых концов
      node->next = node->prev = NULL;
    } else { // В противном случае формируемый элемент заносится в хвост списка
      node->next = NULL;
      node->prev = dest->tail;
      dest->tail->next = node;
      dest->tail = node;
    }
    dest->current = node;    // добавляемый узел становится текущим
    ++(dest->size);          // на один элемент стало больше
    now = now->next;
  }
}

//------------------------------------------------------------------------------
// Получение итератора указывающего на первый элемент
struct ppListIterator* ppList_begin(ppList* l) {
  struct ppListIterator* iter = malloc(sizeof(ppListIterator));
  iter->list = l;
  iter->node = l->head;
  return iter;
}

//------------------------------------------------------------------------------
// Получение итератора указывающего на последний элемент
struct ppListIterator* ppList_end(ppList* l) {
  struct ppListIterator* iter = malloc(sizeof(ppListIterator));
  iter->list = l;
  iter->node = l->tail;
  return iter;
}

//------------------------------------------------------------------------------
// Получение итератора указывающего на текущий элемент
struct ppListIterator* ppList_current_iterator(ppList* l) {
  struct ppListIterator* iter = malloc(sizeof(ppListIterator));
  iter->list = l;
  iter->node = l->current;
  return iter;
}

//------------------------------------------------------------------------------
// Смещение итератора на один элемент вперёд
void ppListIterator_next(ppListIterator* iter) {
  iter->node = iter->node->next;
}

//------------------------------------------------------------------------------
// Смещение итератора на один элемент назад
void ppListIterator_prev(ppListIterator* iter) {
  iter->node = iter->node->prev;
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации списка значения элемента на который ссылается итератор
void ppListIterator_get_value(ppListIterator* iter) {
  memcpy(iter->list->foundation_addr, iter->node->data, iter->list->foundation_size);
}


//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на первый элемент
struct ppListRIterator* ppList_rbegin(ppList* l) {
  struct ppListRIterator* riter = malloc(sizeof(ppListIterator));
  riter->list = l;
  riter->node = l->head;
  return riter;
}

//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на последний элемент
struct ppListRIterator* ppList_rend(ppList* l) {
  struct ppListRIterator* riter = malloc(sizeof(ppListRIterator));
  riter->list = l;
  riter->node = l->tail;
  return riter;
}

//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на текущий элемент
struct ppListRIterator* ppList_current_riterator(ppList* l) {
  struct ppListRIterator* riter = malloc(sizeof(ppListRIterator));
  riter->list = l;
  riter->node = l->current;
  return riter;
}

//------------------------------------------------------------------------------
// Смещение обратного итератора на один элемент назад
void ppListRIterator_next(ppListRIterator* riter) {
  riter->node = riter->node->prev;
}

//------------------------------------------------------------------------------
// Смещение обратного итератора на один элемент вперёд
void ppListRIterator_prev(ppListRIterator* riter) {
  riter->node = riter->node->next;
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации списка значения элемента на который ссылается обратный итератор
void ppListRIterator_get_value(ppListRIterator* riter) {
  memcpy(riter->list->foundation_addr, riter->node->data, riter->list->foundation_size);
}