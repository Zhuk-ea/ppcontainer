#ifndef __ppcontainer_macro__
#define __ppcontainer_macro__

// Макрос для создания специализированной переменной ppContainer
#define ppContainer_VAR(foundation_type, cont_name) \
  struct ppContainer.foundation_type cont_name;     \
  cont_name.foundation_size = sizeof(cont_name.@);  \
  cont_name.foundation_addr = &(cont_name.@);

// Макрос для специализации ppContainer для ppList
// elem_type  - тип элементов списка (например, int)
// spec_name  - имя структуры-обёртки (например, IntListRef)
#define ppContainer_LIST_SPEC(elem_type, spec_name)                                  \
  typedef struct spec_name { struct ppList.elem_type* list; int dummy; } spec_name;  \
  ppContainer+<spec_name;>;                                                          \
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
  }

// Макрос для специализации ppContainer для ppVector
// elem_type  - тип элементов вектора (например, int)
// spec_name  - имя структуры-обёртки (например, IntVectorRef)
#define ppContainer_VECTOR_SPEC(elem_type, spec_name)                                 \
  typedef struct spec_name { struct ppVector.elem_type* vec; int dummy; } spec_name;  \
  ppContainer+<spec_name;>;                                                           \
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
  }

// Макрос для специализации ppContainer для ppMap
// pair_type - имя структуры-пары (должна содержать поля key и value)
// spec_name - имя структуры-обёртки (например, IntMapRef)
#define ppContainer_MAP_SPEC(pair_type, spec_name)                                    \
  typedef struct spec_name { struct ppMap.pair_type* map; int dummy; } spec_name;     \
  ppContainer+<spec_name;>;                                                           \
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
  }

#endif // __ppcontainer_macro__