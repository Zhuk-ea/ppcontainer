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
  if(!l) {
    printf("Incorrect list in  ppList_size function\n");
    exit(-1);
  }
  return l->size;
}

//------------------------------------------------------------------------------
// Установка нового значения в существующий текущий элемент списка
// из значения, находящегося в специализации
_Bool ppList_replace_current(ppList* l) {
  if(l->current == NULL) {
    return 0; // замена не произведена
  }
  // Перенос значения из специализации в текущий узел
  memcpy(l->current->data, l->foundation_addr, l->foundation_size);
  return 1;
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
    free(l->tail);
    l->head = l->current = l->tail = NULL;
    l->size = 0;
    return;
  }
  ppListNode *new_tail = l->tail->prev;
  if (l->current == l->tail) {
    l->current = new_tail;
  }
  free(l->tail);
  l->tail = new_tail;
  l->tail->next = NULL;
  --(l->size);
}

//------------------------------------------------------------------------------
// Удаление первого элемента списка
void ppList_pop_front(ppList* l) {
  if(l->head == NULL) {
    return;
  }
  if(l->size == 1) {
    free(l->head);
    l->head = l->current = l->tail = NULL;
    l->size = 0;
    return;
  }
  ppListNode *new_head = l->head->next;
  if (l->current == l->head) {
    l->current = new_head;
  }
  free(l->head);
  l->head = new_head;
  l->head->prev = NULL;
  --(l->size);
}

//------------------------------------------------------------------------------
// Удаление текущего элемента списка
void ppList_pop_current(ppList* l) {
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
void ppList_swap(ppList* dest, ppList* src) {
  // Проверка однотипности списоков
  if(spec_index_cmp(dest, src) < 1) {
  // Или обобщение или специализации не совпадают
    printf("Incompatible specializations in swap function\n");
    exit(-1);
  }
  // Осуществление обмена
  uint32_t tmp = dest->size; dest->size = src->size; src->size = tmp;
  struct ppListNode* tmp_node_ptr = dest->current; dest->current = src->current; src->current = tmp_node_ptr;
  tmp_node_ptr = dest->head; dest->head = src->head; src->head = tmp_node_ptr;
  tmp_node_ptr = dest->tail; dest->tail = src->tail; src->tail = tmp_node_ptr;
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
// Получение итератора указывающего на первый элемент списка
void ppList_begin(ppList* l, ppListIterator* iter) {
  if(l->head == NULL) {
    printf("Trying to get the beginning of an empty list in ppListIterator_begin function\n");
    exit(-1);
  }
  iter->list = l;
  iter->node = l->head;
}

//------------------------------------------------------------------------------
// Получение итератора указывающего на последний элемент списка
void ppList_end(ppList* l, ppListIterator* iter) {
  if(l->tail == NULL) {
    printf("Trying to get the end of an empty list in ppListIterator_end function\n");
    exit(-1);
  }
  iter->list = l;
  iter->node = l->tail;
}

//------------------------------------------------------------------------------
// Получение итератора указывающего на текущий элемент
void ppList_current_iterator(ppList* l, ppListIterator* iter) {
  iter->list = l;
  iter->node = l->current;
}

//------------------------------------------------------------------------------
// Смещение итератора на один элемент вперёд
_Bool ppListIterator_next(ppListIterator* iter) {
  if(iter->node == NULL) {
    return 0;
  }
  iter->node = iter->node->next;
  return 1;
}

//------------------------------------------------------------------------------
// Смещение итератора на один элемент назад
_Bool ppListIterator_prev(ppListIterator* iter) {
  if(iter->node == NULL) {
    return 0;
  }
  iter->node = iter->node->prev;
  return 1;
}

//------------------------------------------------------------------------------
// Фиксация в основе специализации списка значения элемента на который ссылается итератор
_Bool ppListIterator_get_value(ppListIterator* iter) {
  if (iter->node == NULL) {
    return 0;
  }
  memcpy(iter->list->foundation_addr, iter->node->data, iter->list->foundation_size);
  return 1;
}


//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на первый элемент
void ppList_rbegin(ppList* l, ppListRIterator* riter) {
  if(l->head == NULL) {
    printf("Trying to get the beginning of an empty list in ppListRIterator_begin function\n");
    exit(-1);
  }
  riter->list = l;
  riter->node = l->head;
}

//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на последний элемент
void ppList_rend(ppList* l, ppListRIterator* riter) {
  if(l->tail == NULL) {
    printf("Trying to get the end of an empty list in ppListRIterator_end function\n");
    exit(-1);
  }
  riter->list = l;
  riter->node = l->tail;
}

//------------------------------------------------------------------------------
// Получение обратного итератора указывающего на текущий элемент
void ppList_current_riterator(ppList* l, ppListRIterator* riter) {
  riter->list = l;
  riter->node = l->current;
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

//------------------------------------------------------------------------------
// Вставка нового узла(со значением, записанным в основу специализации) после узла, на который указывает итератор
void ppListIterator_insert_after(ppListIterator* iter) {
  if(iter->node == NULL) {
    printf("Incorrect current value in ppListIterator_insert_after function\n");
    exit(-1);
  }
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + iter->list->foundation_size);
  ppList * l = iter->list;
  if(node == NULL) {
    printf("Incorrect node creation in ppListIterator_insert_after function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, iter->list->foundation_addr, iter->list->foundation_size);
  // Прикрепление созданного узла после того, на который указывает итератор
  node->next = iter->node->next;
  node->prev = iter->node;
  iter->node->next = node;
  if(l->tail == iter->node) { // Для последнего элемента нужно перемещение
    l->tail = node;
  } else { // связь следующего узла с создаваемым
    node->next->prev = node;
  }
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Вставка нового узла(со значением, записанным в основу специализации) перед узлом, на который указывает итератор
void ppListIterator_insert_before(ppListIterator* iter) {
  if(iter->node == NULL) {
    printf("Incorrect node value in ppListIterator_insert_before function\n");
    exit(-1);
  }
  // Создание элемента списка под данные размером в основу специализации
  ppListNode* node = malloc(sizeof(ppListNode) + iter->list->foundation_size);
  ppList * l = iter->list;
  if(node == NULL) {
    printf("Incorrect node creation in ppListIterator_insert_before function\n");
    exit(-1);
  }
  // Перенос значения из специализации в узел
  memcpy(node->data, iter->list->foundation_addr, iter->list->foundation_size);
  // Прикрепление созданного узла перед тем, на который указывает итератор
  node->prev = iter->node->prev;
  node->next = iter->node;
  iter->node->prev = node;
  if(l->head == iter->node) { // Для первого элемента нужно перемещение
    l->head = node;
  } else { // связь предыдущего узла с создаваемым
    node->prev->next = node;
  }
  ++(l->size);          // на один элемент стало больше
}

//------------------------------------------------------------------------------
// Вставка нового значения(записаного в основу специализации) в узел, на который указывает итератор
void ppListIterator_replace(ppListIterator* iter) {
  if(iter->node == NULL) {
    printf("Incorrect node value in ppListIterator_replace function\n");
    exit(-1);
  }
  memcpy(iter->node->data, iter->list->foundation_addr, iter->list->foundation_size);
}


//------------------------------------------------------------------------------
// Удаление из списка элемента на который ссылается обратный итератор, итератор начинает указывать на следующий элемент(если он есть), или предыдущий(если элемент был последним)
void ppListIterator_erase(ppListIterator* iter) {
  ppListNode * t;
  if(iter->node == NULL) {
    printf("Incorrect node value in ppListIterator_erase function\n");
    exit(-1);
  }
  if (iter->node->prev) {
    iter->node->prev->next = iter->node->next;
  } else {
    iter->list->head = iter->list->head->next;
  }
  if (iter->node->next) {
    iter->node->next->prev = iter->node->prev;
    t = iter->node->next;
  } else {
    iter->list->tail = iter->list->tail->prev;
    t = iter->node->prev;
    t->next = NULL;
  }
  if (iter->node == iter->list->current) {
    iter->list->current = t;
  }
  free(iter->node);
  --iter->list->size;
  iter->node = t;
}

//------------------------------------------------------------------------------
// Удаление из списка всех элементов, равных значению, занесённому в специализацию
void ppList_remove(ppList* l) {
  ppListNode * node = l->head;
  while (node) {
    if (!memcmp(node->data, l->foundation_addr, l->foundation_size)) {
      ppListNode *t = node;
      if(node->prev) {
        node->prev->next = node->next;
      } else {
        l->head = l->head->next;
      }
      if (node->next) {
        node->next->prev = node->prev;
      } else {
        l->tail = l->tail->prev;
      }
      node = node->next;
      free(t);
    } else {
      node = node->next;
    }
  }
}


//------------------------------------------------------------------------------
// Удаление из списка всех элементов, соответствующих предикату
void ppList_remove_if(ppList* l, int (*pred)(char *data)) {
  ppListNode * node = l->head;
  while (node) {
    if (pred(node->data)) {
      ppListNode *t = node;
      if(node->prev) {
        node->prev->next = node->next;
      } else {
        l->head = l->head->next;
      }
      if (node->next) {
        node->next->prev = node->prev;
      } else {
        l->tail = l->tail->prev;
      }
      node = node->next;
      free(t);
    } else {
      node = node->next;
    }
  }
}


//------------------------------------------------------------------------------
// Объединение двух отсортированных однотипных списков (если один или оба списка не отсортированны, результат объединения так же не будет отсортирован, но функция ошибки не выдаст)
// Требует реализованную функцию сравнения, которая возвращает 1, если первый элемент меньше второго, 0 в другом случае
void ppList_merge(ppList* dest, ppList* src, int (*cmp)(char *a, char *b)) {
  if (dest == src || src->size == 0) return;

  if (dest->size == 0) {
    dest->head = src->head;
    dest->tail = src->tail;
    dest->current = src->current;
    dest->size = src->size;
    src->head = src->tail = src->current = NULL;
    src->size = 0;
    return;
  }

  ppListNode **dest_ptr = &dest->head;
  ppListNode *now_src = src->head;

  while (*dest_ptr && now_src) {
    if (cmp((*dest_ptr)->data, now_src->data)) {
      dest_ptr = &(*dest_ptr)->next;
    } else {
      ppListNode *temp = now_src->next;

      now_src->prev = (*dest_ptr)->prev;
      now_src->next = *dest_ptr;
      (*dest_ptr)->prev = now_src;
      *dest_ptr = now_src;
      dest_ptr = &now_src->next;

      now_src = temp;
    }
  }

  if (now_src) {
    *dest_ptr = now_src;
    now_src->prev = dest->tail;
    dest->tail = src->tail;
  }

  dest->size += src->size;
  src->head = src->tail = src->current = NULL;
  src->size = 0;
}

//------------------------------------------------------------------------------
// Сравнение двух однотипных списков на равенство(Равны ли все элементы)
// Требует указание размера типа списков в байтах
_Bool ppList_is_equal(ppList* l1, ppList* l2, size_t size) {
  if (l1->size != l2->size) return 0;
  ppListNode * now1 = l1->head;
  ppListNode * now2 = l2->head;
  while (now1) {
    if (memcmp(now1->data, now2->data, size)) return 0;
    now1 = now1->next;
    now2 = now2->next;
  }
  return 1;
}

// Вспомогательная структура для хранения диапазона(в виде временного списка) и узлов между которыми его нужно будет вставить
typedef struct {
  ppList list;
  ppListNode *prev;
  ppListNode *next;
} ExtractedRange;

// Вспомогательная функция
// Вырезает диапазон [src_begin, src_end) из списка (в качестве next и prev берутся узлы, между которыми диапазон находился в исходном списке)
static ExtractedRange extract_range(ppListIterator* src_begin, ppListIterator* src_end) {
  ExtractedRange range = {0};
  if (src_begin->node == src_end->node) return range;

  ppList *src = src_begin->list;
  ppListNode *first = src_begin->node;
  ppListNode *last  = src_end->node ? src_end->node->prev : src->tail;
  ppListNode *prev = first->prev;
  ppListNode *next = src_end->node;

  // подсчёт размера
  int size = 0;
  for (ppListNode *t = first; t != next; t = t->next) {
    ++size;
  }

  ppListNode **prev_link = prev ? &prev->next : &src->head;
  ppListNode **next_link = next ? &next->prev : &src->tail;

  // отсоединение диапазона
  *prev_link = next;
  *next_link = prev;
  first->prev = NULL;
  last->next  = NULL;

  range.list.head = first;
  range.list.tail = last;
  range.list.size = size;
  range.list.current = NULL;

  range.prev = prev;
  range.next = next;

  src->size -= size;
  return range;
}

// Вспомогательная функция
// Вставляет диапазон range между узлами prev и next в список target
static void insert_range(ppList *target, ExtractedRange *range, ppListNode *prev, ppListNode *next) {
  if (range->list.head == NULL) return;
  ppListNode **link_head = prev ? &prev->next : &target->head;
  ppListNode **link_tail = next ? &next->prev : &target->tail;

  *link_head = range->list.head;
  range->list.head->prev = prev;
  *link_tail = range->list.tail;
  range->list.tail->next = next;

  target->size += range->list.size;
}


//------------------------------------------------------------------------------
// Объединение списка и диапазона из другого списка (списки однотипны)
// Попытка объединить диапазоны из одного списка накладывающиеся друг на друга вызывает неопределённое поведение
// Вставляет дианазон после указанной позиции (если pos->node == NULL, вставляет диапазон перед головой списка)
void ppList_splice_after(ppListIterator* pos, ppListIterator* src_begin, ppListIterator* src_end) {
  if(src_begin->list != src_end->list ) {
    printf("Incorrect iterators(begin and end from different lists) in  ppListIterator_splice_after function\n");
    exit(-1);
  }
  if (!pos->list) {
    printf("Incorrect pos iterator(list is NULL) in ppListIterator_splice_after function\n");
    exit(-1);
  }
  if (src_begin->node == src_end->node) return;
  ExtractedRange range = extract_range(src_begin, src_end);
  if (range.list.size == 0) return;

  ppList *target = pos->list;
  ppListNode *prev = pos->node;
  ppListNode *next = prev ? prev->next : target->head;

  insert_range(target, &range, prev, next);

  ppList *src = src_begin->list;
  src->current = range.next ? range.next : range.prev;
}

// Объединение списка и диапазона из другого списка (списки однотипны)
// Попытка объединить диапазоны из одного списка накладывающиеся друг на друга вызывает неопределённое поведение
// Вставляет дианазон перед указанной позиции (если pos->node == NULL, вставляет диапазон после хвоста списка)
void ppList_splice_before(ppListIterator* pos, ppListIterator* src_begin, ppListIterator* src_end) {
  if(src_begin->list != src_end->list ) {
    printf("Incorrect iterators(begin and end from different lists) in  ppListIterator_splice_before function\n");
    exit(-1);
  }
  if (!pos->list) {
    printf("Incorrect pos iterator(list is NULL) in ppListIterator_splice_before function\n");
    exit(-1);
  }
  if (src_begin->node == src_end->node) return; // пустой диапазон
  ExtractedRange range = extract_range(src_begin, src_end);
  if (range.list.size == 0) return;

  ppList *target = pos->list;
  ppListNode *prev = pos->node ? pos->node->prev : target->tail;
  ppListNode *next = pos->node;

  insert_range(target, &range, prev, next);

  ppList *src = src_begin->list;
  src->current = range.next ? range.next : range.prev;
}

//------------------------------------------------------------------------------
// Объединение двух диапазонов из однотипных списков (если один или оба диапозона не отсортированны, результат объединения так же не будет отсортирован, но функция ошибки не выдаст)
// Попытка объединить диапазоны из одного списка накладывающиеся друг на друга вызывает неопределённое поведение
// Требует реализованную функцию сравнения, которая возвращает 1, если первый элемент меньше второго, 0 в другом случае
// Переставляет current для списка из которого взят второй интервал на первый элемент после диапазона(если он есть, если нет, то на последний элемент перед диапазоном)
void ppListIterator_merge_ranges(ppListIterator* dest_begin, ppListIterator* dest_end, ppListIterator* src_begin, ppListIterator* src_end,  int (*cmp)(char *a, char *b)) {
  if(dest_begin->list != dest_end->list || src_begin->list != src_end->list ) {
    printf("Incorrect iterators(begin and end from different lists) in  ppListIterator_merge_ranges function\n");
    exit(-1);
  }
  if (src_begin->node == src_end->node) return;

  // если пустой dest просто вставляем src перед dest_begin
  if (dest_begin->node == dest_end->node) {
    ppList_splice_before(dest_begin, src_begin, src_end);
    return;
  }

  // вырезание диапазонов
  ExtractedRange dest_range = extract_range(dest_begin, dest_end);
  ExtractedRange src_range  = extract_range(src_begin, src_end);

  ppList_merge(&dest_range.list, &src_range.list, cmp);

  // вставка результата merge в dest
  insert_range(dest_begin->list, &dest_range, dest_range.prev, dest_range.next);

  src_begin->list->current = src_range.next ? src_range.next : src_range.prev;
}

//------------------------------------------------------------------------------
// Удаление из списка ПОСЛЕДОВАТЕЛЬНЫХ дубликатов оставляя только первый встретившийся
// Чтобы удалить все дубликаты, нужно сначала отсортировать список
// Требует указание размера элементов хранимых в списках
void ppList_unique(ppList* l, size_t size) {
  if(!l) {
    printf("Incorrect list in ppList_unique function\n");
    exit(-1);
  }
  if (l == NULL || l->head == NULL) return;

  ppListNode *now = l->head;

  while (now != NULL && now->next != NULL) {
    if (memcmp(now->data, now->next->data, size) == 0) {

      ppListNode *duplicate = now->next;
      now->next = duplicate->next;
      if (duplicate->next != NULL) {
        duplicate->next->prev = now;
      } else {
        l->tail = now;
      }

      free(duplicate);
      l->size--;
    } else {
      now = now->next;
    }
  }
}

//------------------------------------------------------------------------------
// Проверка, пуст ли список. 
// Так же проверяет, не "испорчены" ли данные в основной структуре списка 
// (есть указатели куда-либо, несмотря на то, что размер = 0) и в таком случае выдаёт ошибку
_Bool ppList_empty(ppList* list) {
  if(!list) {
    printf("Incorrect list in ppList_empty function\n");
    exit(-1);
  }
  if (list->size != 0) {
    if (list->head == NULL || list->tail== NULL) {
      printf("Incorrect head or tail in non-empty list in ppList_empty function\n");
      exit(-1);
    }
    return 0;
  }
  if (list->size == 0) {
    if (list->head != NULL || list->tail != NULL) {
      printf("Incorrect head or tail in empty list in ppList_empty function\n");
      exit(-1);
    }
  }
  return 1;
}


//------------------------------------------------------------------------------
// Переворачивание списка
void ppList_reverse(ppList* l) {
  if(!l) {
    printf("Incorrect list in ppList_reverse function\n");
    exit(-1);
  }
  if (ppList_empty(l)) return;

  ppListNode *current = l->head;
  ppListNode *temp = NULL;

  while (current != NULL) {
      temp = current->next;
      current->next = current->prev;
      current->prev = temp;
      current = temp;
  }

  temp = l->head;
  l->head = l->tail;
  l->tail = temp;
}
