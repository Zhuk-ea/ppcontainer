#include <stdio.h>
#include "ppmap.h"
#include "test-ppmap-common.h"

typedef struct IntPair { 
    int key; 
    int value; 
} IntPair;

ppMap+<IntPair;>;

void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
    fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

// Глобальные переменные для проверки порядка
static int last_key = -1;
int called = 0;
void empty_cb(void* k, void* v) { called = 1; }

void check_sorted_callback(void* key, void* value) {
    int k = *(int*)key;
    if (k <= last_key) {
        printf("Incorrect order: %d after %d\n", k, last_key);
        exit(1);
    }
    last_key = k;
}

int main(void) {
    int errors = 0;
    printf("=== TEST traverse order ===\n");
    ppMap_VAR(IntPair, map);
    ppMap_init((ppMap*)&map, cmp_int);

    // Вставка в произвольном порядке
    int keys[] = {50, 20, 70, 10, 30, 60, 80};
    int vals[] = {500,200,700,100,300,600,800};
    ppMap_FILL_FROM_ARRAYS(map, keys, vals, 7);

    // Проверка обхода простым callback
    last_key = -1;
    ppMap_traverse((ppMap*)&map, check_sorted_callback);
    test_check_condition(1, "traverse in sorted order", &errors);

    // Проверка обхода с user_data (сбор ключей и сравнение с ожидаемым массивом)
    int expected_keys[] = {10,20,30,50,60,70,80};
    int expected_vals[] = {100,200,300,500,600,700,800};
    check_map_int_content((ppMap*)&map, expected_keys, expected_vals, 7, &errors, "traverse_with_data collects correct pairs");

    // Проверка на пустом отображении
    ppMap_clear((ppMap*)&map);
    ppMap_traverse((ppMap*)&map, empty_cb);
    test_check_condition(!called, "traverse on empty map does nothing", &errors);

    printf("\nTotal errors: %d\n", errors);
    return errors;
}