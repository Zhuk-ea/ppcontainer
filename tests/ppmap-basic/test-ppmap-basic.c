#include <stdio.h>
#include "ppmap.h"

//==============================================================================
// Специализация для int -> int
//==============================================================================
typedef struct IntPair {
    int key;
    int value;
} IntPair;

ppMap+<IntPair;>;

//------------------------------------------------------------------------------
// Обработчик вывода элемента (для ppMap_print)
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
    fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
// Вспомогательные функции (стиль pplist)
void check_condition(int condition, const char* msg, int* errors) {
    if (condition) {
        printf("Correct | %s\n", msg);
    } else {
        printf("Incorrect | %s\n", msg);
        (*errors)++;
    }
}

void print_map(ppMap* m, const char* name) {
    printf("%s: ", name);
    ppMap_print(stdout, m);
}

int cmp_int(const void* a, const void* b) {
    int ia = *(int*)a, ib = *(int*)b;
    return (ia > ib) - (ia < ib);
}

//------------------------------------------------------------------------------
int main(void) {
    int errors = 0;
    printf("\n-------------------------------------------\n\n");
    printf("BASIC TESTS\n\n");

    // 1. init, empty, size
    ppMap_VAR(IntPair, map);
    ppMap_init((ppMap*)&map, cmp_int);
    check_condition(ppMap_empty((ppMap*)&map), "initially empty", &errors);
    check_condition(ppMap_size((ppMap*)&map) == 0, "size 0 after init", &errors);

    // 2. вставка нескольких элементов
    int keys[] = {5, 2, 8, 1, 9};
    int vals[] = {50, 20, 80, 10, 90};
    ppMap_FILL_FROM_ARRAYS(map, keys, vals, 5);
    check_condition(ppMap_size((ppMap*)&map) == 5, "size after insert", &errors);
    check_condition(!ppMap_empty((ppMap*)&map), "not empty after insert", &errors);

    // 3. очистка
    ppMap_CLEAR(map);
    check_condition(ppMap_empty((ppMap*)&map), "empty after clear", &errors);
    check_condition(ppMap_size((ppMap*)&map) == 0, "size 0 after clear", &errors);

    // 4. is_equal для одинаковых и разных отображений
    ppMap_VAR(IntPair, m1);
    ppMap_VAR(IntPair, m2);
    ppMap_init((ppMap*)&m1, cmp_int);
    ppMap_init((ppMap*)&m2, cmp_int);

    ppMap_INSERT(m1, 1, 10);
    ppMap_INSERT(m1, 2, 20);
    ppMap_INSERT(m2, 1, 10);
    ppMap_INSERT(m2, 2, 20);

    check_condition(ppMap_IS_EQUAL(m1, m2), "equal maps", &errors);

    ppMap_INSERT(m2, 3, 30);
    check_condition(!ppMap_IS_EQUAL(m1, m2), "different sizes -> not equal", &errors);

    ppMap_ERASE(m2, 3);
    ppMap_CLEAR(m2);
    ppMap_INSERT(m2, 1, 100); // значение отличается
    ppMap_INSERT(m2, 2, 20);
    check_condition(!ppMap_IS_EQUAL(m1, m2), "same keys, different values -> not equal", &errors);

    printf("\n-------------------------------------------\n\n");
    printf("Total errors: %d\n", errors);
    return errors;
}