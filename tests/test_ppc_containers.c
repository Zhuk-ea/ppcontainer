// test_ppc_containers.c – простой тест установленной библиотеки
#include <stdio.h>
#include <string.h>
#include <ppc_containers/ppcontainer.h>
#include <ppc_containers/pplist.h>
#include <ppc_containers/ppvector.h>
#include <ppc_containers/ppmap.h>

// ============================================================================
// Специализация для целочисленных значений
// ============================================================================

// Для списка
ppList+<int;>;
void ppList_element_print<ppList.int* l>(FILE* f) {
    fprintf(f, "%d ", l->@);
}

// Для вектора
ppVector+<int;>;
void ppVector_element_print<ppVector.int* v>(FILE* f) {
    fprintf(f, "%d ", v->@);
}

// Для отображения (int -> int)
typedef struct IntPair {
    int key;
    int value;
} IntPair;

ppMap+<IntPair;>;
int cmp_int(const void* a, const void* b) {
    int ia = *(int*)a, ib = *(int*)b;
    return (ia > ib) - (ia < ib);
}
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
    fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

// ============================================================================
// Обёртки ppContainer для всех трёх типов (используем макросы)
// ============================================================================
ppContainer_LIST_SPEC(int, IntListRef)
ppContainer_VECTOR_SPEC(int, IntVectorRef)
ppContainer_MAP_SPEC(IntPair, IntMapRef)

// Простой callback для for_each
void print_int_val(void* val) {
    int v;
    memcpy(&v, val, sizeof(int));
    printf("%d ", v);
}

int main() {
    printf("\n=== Testing ppList ===\n");
    ppList_VAR(int, my_list);
    for (int i = 1; i <= 5; ++i) {ppList_PUSH_BACK(my_list, i * 10);}
    ppList_print2(stdout, (ppList*)&my_list);
    printf("\n");

    IntListRef list_ref = { &my_list, 0 };
    ppContainer_VAR(IntListRef, wrapper_list);
    wrapper_list.@ = list_ref;

    printf("Container size: %u\n", ppContainer_size<&wrapper_list>());
    printf("Container empty: %d\n", ppContainer_empty<&wrapper_list>());
    printf("for_each result: ");
    ppContainer_for_each<&wrapper_list>(print_int_val);
    printf("\n");

    printf("\n=== Testing ppVector ===\n");
    ppVector_VAR(int, my_vec);
    for (int i = 1; i <= 5; ++i) {ppVector_PUSH_BACK(my_vec, i * 10);}
    ppVector_print(stdout, (ppVector*)&my_vec);
    printf("\n");

    IntVectorRef vec_ref = { &my_vec, 0 };
    ppContainer_VAR(IntVectorRef, wrapper_vec);
    wrapper_vec.@ = vec_ref;

    printf("Container size: %u\n", ppContainer_size<&wrapper_vec>());
    printf("Container empty: %d\n", ppContainer_empty<&wrapper_vec>());
    printf("for_each result: ");
    ppContainer_for_each<&wrapper_vec>(print_int_val);
    printf("\n");

    printf("\n=== Testing ppMap ===\n");
    ppMap_VAR(IntPair, my_map, cmp_int);
    for (int i = 1; i <= 5; ++i) {ppMap_INSERT(my_map, i, i * 100);}
    ppMap_print(stdout, (ppMap*)&my_map);
    printf("\n");

    IntMapRef map_ref = { &my_map, 0 };
    ppContainer_VAR(IntMapRef, wrapper_map);
    wrapper_map.@ = map_ref;

    printf("Container size: %u\n", ppContainer_size<&wrapper_map>());
    printf("Container empty: %d\n", ppContainer_empty<&wrapper_map>());
    printf("for_each result (values only): ");
    ppContainer_for_each<&wrapper_map>(print_int_val);
    printf("\n");

    // Очистка
    ppList_clear((ppList*)&my_list);
    ppVector_destroy((ppVector*)&my_vec);
    ppMap_clear((ppMap*)&my_map);
    printf("\nAll tests completed.\n");
    return 0;
}