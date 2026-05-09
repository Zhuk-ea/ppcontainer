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

int main(void) {
    int errors = 0;
    printf("=== TEST insert/find/erase ===\n");
    ppMap_VAR(IntPair, map);
    ppMap_init((ppMap*)&map, cmp_int);

    // Вставка
    ppMap_INSERT(map, 10, 100);
    ppMap_INSERT(map, 20, 200);
    ppMap_INSERT(map, 5, 50);
    test_check_condition(ppMap_size((ppMap*)&map) == 3, "size after inserts", &errors);

    // Поиск существующего
    int val;
    ppMap_FIND(map, 20, val);
    test_check_condition(val == 200, "find existing key 20", &errors);
    ppMap_FIND(map, 5, val);
    test_check_condition(val == 50, "find existing key 5", &errors);

    // Поиск отсутствующего
    val = 0;
    ppMap_FIND(map, 99, val);
    test_check_condition(val == 0, "find non-existing key returns unchanged dest", &errors);

    // Замена значения при повторной вставке
    ppMap_INSERT(map, 10, 999);
    ppMap_FIND(map, 10, val);
    test_check_condition(val == 999, "re-insert updates value", &errors);
    test_check_condition(ppMap_size((ppMap*)&map) == 3, "size unchanged after update", &errors);

    // Удаление существующего ключа
    _Bool erased = ppMap_ERASE(map, 20);
    test_check_condition(erased, "erase returns true for existing key", &errors);
    test_check_condition(ppMap_size((ppMap*)&map) == 2, "size decreased", &errors);
    val = 0;
    ppMap_FIND(map, 20, val);
    test_check_condition(val == 0, "key 20 no longer exists", &errors);

    // Удаление отсутствующего ключа
    erased = ppMap_ERASE(map, 100);
    test_check_condition(!erased, "erase returns false for non-existing key", &errors);
    test_check_condition(ppMap_size((ppMap*)&map) == 2, "size unchanged", &errors);

    // Удаление всех элементов по одному
    ppMap_ERASE(map, 10);
    ppMap_ERASE(map, 5);
    test_check_condition(ppMap_empty((ppMap*)&map), "empty after erasing all", &errors);

    printf("\nTotal errors: %d\n", errors);
    return errors;
}