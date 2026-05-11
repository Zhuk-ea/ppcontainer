#ifndef __ppcontainer_macro__
#define __ppcontainer_macro__

#include <stdlib.h>
#include <string.h>

// Макрос для создания специализированной переменной ppContainer
#define ppContainer_VAR(foundation_type, cont_name) \
  struct ppContainer.foundation_type cont_name;     \
  cont_name.foundation_size = sizeof(cont_name.@);  \
  cont_name.foundation_addr = &(cont_name.@);

#define ppContainerIterator_VAR(spec_name, it_name) \
  struct ppContainerIterator.spec_name it_name;
#define ppContainerRIterator_VAR(spec_name, rit_name) \
  struct ppContainerRIterator.spec_name rit_name;

// Макрос для специализации ppContainer для ppList
// elem_type  - тип элементов списка (например, int)
// spec_name  - имя структуры-обёртки (например, IntListRef)
#define ppContainer_LIST_SPEC(elem_type, spec_name)                                  \
  typedef struct spec_name { struct ppList.elem_type* list; int dummy; } spec_name;  \
  ppContainer+<spec_name;>;                                                          \
  ppContainerIterator+<spec_name;>;                                                  \
  ppContainerRIterator+<spec_name;>;                                                 \
  uint32_t ppContainer_size<ppContainer.spec_name* c>() {                            \
    return ppList_size((ppList*)c->@.list);                                          \
  }                                                                                  \
  void ppContainer_print<ppContainer.spec_name* c>(FILE* f) {                        \
    ppList_print2(f, (ppList*)c->@.list);                                            \
  }                                                                                  \
  _Bool ppContainer_empty<ppContainer.spec_name* c>() {                              \
    return ppList_empty((ppList*)c->@.list);                                         \
  }                                                                                  \
  void ppContainer_clear<ppContainer.spec_name* c>() {                               \
    ppList_clear((ppList*)c->@.list);                                                \
  }                                                                                  \
  void ppContainer_copy<ppContainer.spec_name* dest, ppContainer.spec_name* src>() { \
    ppList_copy((ppList*)((spec_name*)dest->foundation_addr)->list,                  \
                (ppList*)((spec_name*)src->foundation_addr)->list);                  \
  }                                                                                  \
  void ppContainer_move<ppContainer.spec_name* dest, ppContainer.spec_name* src>() { \
    ppList_move((ppList*)((spec_name*)dest->foundation_addr)->list,                  \
                (ppList*)((spec_name*)src->foundation_addr)->list);                  \
  }                                                                                  \
  void ppContainer_swap<ppContainer.spec_name* a, ppContainer.spec_name* b>() {      \
    ppList_swap((ppList*)((spec_name*)a->foundation_addr)->list,                     \
                (ppList*)((spec_name*)b->foundation_addr)->list);                    \
  }                                                                                  \
  void ppContainer_begin<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                 \
    ppListIterator* li = (ppListIterator*)malloc(sizeof(ppListIterator));            \
    ppList_begin((ppList*)c->@.list, li);                                            \
    it->internal_iter = li;                                                          \
  }                                                                                  \
  void ppContainer_end<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                 \
    ppListIterator* li = (ppListIterator*)malloc(sizeof(ppListIterator));            \
    ppList_end((ppList*)c->@.list, li);                                              \
    it->internal_iter = li;                                                          \
  }                                                                                  \
  _Bool ppContainerIterator_next<ppContainerIterator.spec_name* it>() {              \
    ppListIterator* li = (ppListIterator*)it->internal_iter;                         \
    return ppListIterator_next(li);                                                  \
  }                                                                                  \
  _Bool ppContainerIterator_prev<ppContainerIterator.spec_name* it>() {              \
    ppListIterator* li = (ppListIterator*)it->internal_iter;                         \
    return ppListIterator_prev(li);                                                  \
  }                                                                                  \
  _Bool ppContainerIterator_get_value<ppContainerIterator.spec_name* it>() {         \
    ppListIterator* li = (ppListIterator*)it->internal_iter;                         \
    _Bool ok = ppListIterator_get_value(li);                                         \
    if (ok) {                                                                        \
      ppContainer* cont = it->container;                                             \
      memcpy(cont->foundation_addr, li->list->foundation_addr, cont->foundation_size); \
    }                                                                                \
    return ok;                                                                       \
  }                                                                                  \
  void ppContainerIterator_free<ppContainerIterator.spec_name* it>() {               \
    if (it->internal_iter) { free(it->internal_iter); it->internal_iter = NULL; }    \
  }                                                                                  \
  void ppContainer_rbegin<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                \
    ppListRIterator* ri = (ppListRIterator*)malloc(sizeof(ppListRIterator));         \
    ppList_rbegin((ppList*)c->@.list, ri);                                           \
    rit->internal_riter = ri;                                                        \
  }                                                                                  \
  void ppContainer_rend<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                \
    ppListRIterator* ri = (ppListRIterator*)malloc(sizeof(ppListRIterator));         \
    ppList_rend((ppList*)c->@.list, ri);                                             \
    rit->internal_riter = ri;                                                        \
  }                                                                                  \
  _Bool ppContainerRIterator_next<ppContainerRIterator.spec_name* rit>() {           \
    ppListRIterator* ri = (ppListRIterator*)rit->internal_riter;                     \
    return ppListRIterator_next(ri);                                                 \
  }                                                                                  \
  _Bool ppContainerRIterator_prev<ppContainerRIterator.spec_name* rit>() {           \
    ppListRIterator* ri = (ppListRIterator*)rit->internal_riter;                     \
    return ppListRIterator_prev(ri);                                                 \
  }                                                                                  \
  _Bool ppContainerRIterator_get_value<ppContainerRIterator.spec_name* rit>() {      \
    ppListRIterator* ri = (ppListRIterator*)rit->internal_riter;                     \
    _Bool ok = ppListRIterator_get_value(ri);                                        \
    if (ok) {                                                                        \
      ppContainer* cont = rit->container;                                            \
      memcpy(cont->foundation_addr, ri->list->foundation_addr, cont->foundation_size); \
    }                                                                                \
    return ok;                                                                       \
  }                                                                                  \
  void ppContainerRIterator_free<ppContainerRIterator.spec_name* rit>() {            \
    if (rit->internal_riter) { free(rit->internal_riter); rit->internal_riter = NULL; } \
  }                                                                                  \
  void ppContainer_for_each<ppContainer.spec_name* c>(void (*callback)(void*)) {     \
    if (ppContainer_empty<c>()) return;                                              \
    struct ppContainerIterator.spec_name it;                                         \
    ppContainer_begin<c, &it>();                                                     \
    do {                                                                             \
        if (ppContainerIterator_get_value<&it>()) {                                  \
            callback(c->foundation_addr);                                            \
        }                                                                            \
    } while (ppContainerIterator_next<&it>());                                       \
    ppContainerIterator_free<&it>();                                                 \
  }

// Макрос для специализации ppContainer для ppVector
// elem_type  - тип элементов вектора (например, int)
// spec_name  - имя структуры-обёртки (например, IntVectorRef)
#define ppContainer_VECTOR_SPEC(elem_type, spec_name)                                 \
  typedef struct spec_name { struct ppVector.elem_type* vec; int dummy; } spec_name;  \
  ppContainer+<spec_name;>;                                                           \
  ppContainerIterator+<spec_name;>;                                                   \
  ppContainerRIterator+<spec_name;>;                                                  \
  uint32_t ppContainer_size<ppContainer.spec_name* c>() {                             \
    return ppVector_size((ppVector*)c->@.vec);                                        \
  }                                                                                   \
  void ppContainer_print<ppContainer.spec_name* c>(FILE* f) {                         \
    ppVector_print(f, (ppVector*)c->@.vec);                                           \
  }                                                                                   \
  _Bool ppContainer_empty<ppContainer.spec_name* c>() {                               \
    return ppVector_size((ppVector*)c->@.vec) == 0;                                   \
  }                                                                                   \
  void ppContainer_clear<ppContainer.spec_name* c>() {                                \
    ppVector_clear((ppVector*)c->@.vec);                                              \
  }                                                                                   \
  void ppContainer_copy<ppContainer.spec_name* dest, ppContainer.spec_name* src>() {  \
    ppVector_copy((ppVector*)((spec_name*)dest->foundation_addr)->vec,                \
                  (ppVector*)((spec_name*)src->foundation_addr)->vec);                \
  }                                                                                   \
  void ppContainer_move<ppContainer.spec_name* dest, ppContainer.spec_name* src>() {  \
    ppVector_move((ppVector*)((spec_name*)dest->foundation_addr)->vec,                \
                  (ppVector*)((spec_name*)src->foundation_addr)->vec);                \
  }                                                                                   \
  void ppContainer_swap<ppContainer.spec_name* a, ppContainer.spec_name* b>() {       \
    ppVector_swap((ppVector*)((spec_name*)a->foundation_addr)->vec,                   \
                  (ppVector*)((spec_name*)b->foundation_addr)->vec);                  \
  }                                                                                   \
  void ppContainer_begin<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                  \
    ppVectorIterator* vi = (ppVectorIterator*)malloc(sizeof(ppVectorIterator));       \
    ppVector_begin((ppVector*)c->@.vec, vi);                                          \
    it->internal_iter = vi;                                                           \
  }                                                                                   \
  void ppContainer_end<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                  \
    ppVectorIterator* vi = (ppVectorIterator*)malloc(sizeof(ppVectorIterator));       \
    ppVector_end((ppVector*)c->@.vec, vi);                                            \
    it->internal_iter = vi;                                                           \
  }                                                                                   \
  _Bool ppContainerIterator_next<ppContainerIterator.spec_name* it>() {               \
    ppVectorIterator* vi = (ppVectorIterator*)it->internal_iter;                      \
    return ppVectorIterator_next(vi);                                                 \
  }                                                                                   \
  _Bool ppContainerIterator_prev<ppContainerIterator.spec_name* it>() {               \
    ppVectorIterator* vi = (ppVectorIterator*)it->internal_iter;                      \
    return ppVectorIterator_prev(vi);                                                 \
  }                                                                                   \
  _Bool ppContainerIterator_get_value<ppContainerIterator.spec_name* it>() {          \
    ppVectorIterator* vi = (ppVectorIterator*)it->internal_iter;                      \
    _Bool ok = ppVectorIterator_get_value(vi);                                        \
    if (ok) {                                                                         \
      ppContainer* cont = it->container;                                              \
      memcpy(cont->foundation_addr, vi->vector->foundation_addr, cont->foundation_size); \
    }                                                                                 \
    return ok;                                                                        \
  }                                                                                   \
  void ppContainerIterator_free<ppContainerIterator.spec_name* it>() {                \
    if (it->internal_iter) { free(it->internal_iter); it->internal_iter = NULL; }     \
  }                                                                                   \
  void ppContainer_rbegin<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                 \
    ppVectorRIterator* rvi = (ppVectorRIterator*)malloc(sizeof(ppVectorRIterator));   \
    ppVector_rbegin((ppVector*)c->@.vec, rvi);                                        \
    rit->internal_riter = rvi;                                                        \
  }                                                                                   \
  void ppContainer_rend<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                 \
    ppVectorRIterator* rvi = (ppVectorRIterator*)malloc(sizeof(ppVectorRIterator));   \
    ppVector_rend((ppVector*)c->@.vec, rvi);                                          \
    rit->internal_riter = rvi;                                                        \
  }                                                                                   \
  _Bool ppContainerRIterator_next<ppContainerRIterator.spec_name* rit>() {            \
    ppVectorRIterator* rvi = (ppVectorRIterator*)rit->internal_riter;                 \
    return ppVectorRIterator_next(rvi);                                               \
  }                                                                                   \
  _Bool ppContainerRIterator_prev<ppContainerRIterator.spec_name* rit>() {            \
    ppVectorRIterator* rvi = (ppVectorRIterator*)rit->internal_riter;                 \
    return ppVectorRIterator_prev(rvi);                                               \
  }                                                                                   \
  _Bool ppContainerRIterator_get_value<ppContainerRIterator.spec_name* rit>() {       \
    ppVectorRIterator* rvi = (ppVectorRIterator*)rit->internal_riter;                 \
    _Bool ok = ppVectorRIterator_get_value(rvi);                                      \
    if (ok) {                                                                         \
      ppContainer* cont = rit->container;                                             \
      memcpy(cont->foundation_addr, rvi->vector->foundation_addr, cont->foundation_size); \
    }                                                                                 \
    return ok;                                                                        \
  }                                                                                   \
  void ppContainerRIterator_free<ppContainerRIterator.spec_name* rit>() {             \
    if (rit->internal_riter) { free(rit->internal_riter); rit->internal_riter = NULL; } \
  }                                                                                   \
  void ppContainer_for_each<ppContainer.spec_name* c>(void (*callback)(void*)) {      \
  if (ppContainer_empty<c>()) return;                                                   \
  struct ppContainerIterator.spec_name it;                                            \
  ppContainer_begin<c, &it>();                                               \
  do {                                                                       \
    if (ppContainerIterator_get_value<&it>()) {                              \
      callback(c->foundation_addr);                                          \
    }                                                                        \
  } while (ppContainerIterator_next<&it>());                                 \
  ppContainerIterator_free<&it>();                                           \
}

// Макрос для специализации ppContainer для ppMap
// pair_type - имя структуры-пары (должна содержать поля key и value)
// spec_name - имя структуры-обёртки (например, IntMapRef)
#define ppContainer_MAP_SPEC(pair_type, spec_name)                                    \
  typedef struct spec_name { struct ppMap.pair_type* map; int dummy; } spec_name;     \
  ppContainer+<spec_name;>;                                                          \
  ppContainerIterator+<spec_name;>;                                                  \
  ppContainerRIterator+<spec_name;>;                                                \
  uint32_t ppContainer_size<ppContainer.spec_name* c>() {                             \
    return ppMap_size((ppMap*)c->@.map);                                              \
  }                                                                                   \
  void ppContainer_print<ppContainer.spec_name* c>(FILE* f) {                         \
    ppMap_print(f, (ppMap*)c->@.map);                                                 \
  }                                                                                   \
  _Bool ppContainer_empty<ppContainer.spec_name* c>() {                               \
    return ppMap_empty((ppMap*)c->@.map);                                             \
  }                                                                                   \
  void ppContainer_clear<ppContainer.spec_name* c>() {                                \
    ppMap_clear((ppMap*)c->@.map);                                                    \
  }                                                                                   \
  void ppContainer_copy<ppContainer.spec_name* dest, ppContainer.spec_name* src>() {  \
    ppMap_copy((ppMap*)((spec_name*)dest->foundation_addr)->map,                      \
               (ppMap*)((spec_name*)src->foundation_addr)->map);                      \
  }                                                                                   \
  void ppContainer_move<ppContainer.spec_name* dest, ppContainer.spec_name* src>() {  \
    ppMap_move((ppMap*)((spec_name*)dest->foundation_addr)->map,                      \
               (ppMap*)((spec_name*)src->foundation_addr)->map);                      \
  }                                                                                   \
  void ppContainer_swap<ppContainer.spec_name* a, ppContainer.spec_name* b>() {       \
    ppMap_swap((ppMap*)((spec_name*)a->foundation_addr)->map,                         \
               (ppMap*)((spec_name*)b->foundation_addr)->map);                        \
  }                                                                                   \
  void ppContainer_begin<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                 \
    ppMapIterator* mi = (ppMapIterator*)malloc(sizeof(ppMapIterator));               \
    ppMap_begin((ppMap*)c->@.map, mi);                                               \
    it->internal_iter = mi;                                                          \
  }                                                                                  \
  void ppContainer_end<ppContainer.spec_name* c, ppContainerIterator.spec_name* it>() { \
    it->container = (ppContainer*)c;                                                 \
    ppMapIterator* mi = (ppMapIterator*)malloc(sizeof(ppMapIterator));               \
    ppMap_end((ppMap*)c->@.map, mi);                                                 \
    it->internal_iter = mi;                                                          \
  }                                                                                  \
  _Bool ppContainerIterator_next<ppContainerIterator.spec_name* it>() {              \
    ppMapIterator* mi = (ppMapIterator*)it->internal_iter;                           \
    return ppMapIterator_next(mi);                                                   \
  }                                                                                  \
  _Bool ppContainerIterator_prev<ppContainerIterator.spec_name* it>() {              \
    ppMapIterator* mi = (ppMapIterator*)it->internal_iter;                           \
    return ppMapIterator_prev(mi);                                                   \
  }                                                                                  \
  _Bool ppContainerIterator_get_value<ppContainerIterator.spec_name* it>() {         \
    ppMapIterator* mi = (ppMapIterator*)it->internal_iter;                           \
    _Bool ok = ppMapIterator_get_value(mi);                                          \
    if (ok) {                                                                        \
      ppContainer* cont = it->container;                                             \
      void* value_addr = (char*)mi->map->foundation_addr + mi->map->key_size;        \
      memcpy(cont->foundation_addr, value_addr, cont->foundation_size);              \
    }                                                                                \
    return ok;                                                                       \
  }                                                                                  \
  void ppContainerIterator_free<ppContainerIterator.spec_name* it>() {               \
    if (it->internal_iter) { free(it->internal_iter); it->internal_iter = NULL; }    \
  }                                                                                  \
  void ppContainer_rbegin<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                \
    ppMapRIterator* rmi = (ppMapRIterator*)malloc(sizeof(ppMapRIterator));           \
    ppMap_rbegin((ppMap*)c->@.map, rmi);                                             \
    rit->internal_riter = rmi;                                                       \
  }                                                                                  \
  void ppContainer_rend<ppContainer.spec_name* c, ppContainerRIterator.spec_name* rit>() { \
    rit->container = (ppContainer*)c;                                                \
    ppMapRIterator* rmi = (ppMapRIterator*)malloc(sizeof(ppMapRIterator));           \
    ppMap_rend((ppMap*)c->@.map, rmi);                                               \
    rit->internal_riter = rmi;                                                       \
  }                                                                                  \
  _Bool ppContainerRIterator_next<ppContainerRIterator.spec_name* rit>() {           \
    ppMapRIterator* rmi = (ppMapRIterator*)rit->internal_riter;                      \
    return ppMapRIterator_next(rmi);                                                 \
  }                                                                                  \
  _Bool ppContainerRIterator_prev<ppContainerRIterator.spec_name* rit>() {           \
    ppMapRIterator* rmi = (ppMapRIterator*)rit->internal_riter;                      \
    return ppMapRIterator_prev(rmi);                                                 \
  }                                                                                  \
  _Bool ppContainerRIterator_get_value<ppContainerRIterator.spec_name* rit>() {      \
    ppMapRIterator* rmi = (ppMapRIterator*)rit->internal_riter;                      \
    _Bool ok = ppMapRIterator_get_value(rmi);                                        \
    if (ok) {                                                                        \
      ppContainer* cont = rit->container;                                            \
      void* value_addr = (char*)rmi->map->foundation_addr + rmi->map->key_size;      \
      memcpy(cont->foundation_addr, value_addr, cont->foundation_size);              \
    }                                                                                \
    return ok;                                                                       \
  }                                                                                  \
  void ppContainerRIterator_free<ppContainerRIterator.spec_name* rit>() {            \
    if (rit->internal_riter) { free(rit->internal_riter); rit->internal_riter = NULL; } \
  }                                                                                  \
  void ppContainer_for_each<ppContainer.spec_name* c>(void (*callback)(void*)) {     \
    if (ppContainer_empty<c>()) return;                                                \
    struct ppContainerIterator.spec_name it;                                         \
    ppContainer_begin<c, &it>();                                                     \
    do {                                                                             \
      if (ppContainerIterator_get_value<&it>()) {                                    \
        callback(c->foundation_addr);                                                \
      }                                                                              \
    } while (ppContainerIterator_next<&it>());                                       \
    ppContainerIterator_free<&it>();                                                 \
} 

#endif // __ppcontainer_macro__