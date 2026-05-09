#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ppmap.h"
#include "test-ppmap-common.h"

typedef struct IntPair { int key; int value; } IntPair;
ppMap+<IntPair;>;

void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
    fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

static void random_pair(int* key, int* value, int range) {
    *key = rand() % range;
    *value = rand() % range;
}

static size_t traverse_counter = 0;
static void count_callback(void* key, void* value) {
    (void)key; (void)value;
    traverse_counter++;
}

int main(void) {
    srand((unsigned)time(NULL));
    int errors = 0;
    printf("=== STRESS TEST with RB properties check ===\n");

    ppMap_VAR(IntPair, map);
    ppMap_init((ppMap*)&map, cmp_int);

    const int N_OPS = 10000;
    const int KEY_RANGE = 500;

    for (int i = 0; i < N_OPS; ++i) {
        int op = rand() % 3; // 0=insert, 1=find, 2=erase
        int key, val;
        random_pair(&key, &val, KEY_RANGE);
        switch (op) {
            case 0:
                ppMap_INSERT(map, key, val);
                break;
            case 1: {
                int found_val;
                ppMap_FIND(map, key, found_val);
                break;
            }
            case 2:
                ppMap_ERASE(map, key);
                break;
        }

        // Проверка свойств каждые 100 операций (или после последней)
        if ((i + 1) % 100 == 0 || i == N_OPS - 1) {
            // 1. Проверка RB-свойств
            ppMap_check_rb_properties((ppMap*)&map, &errors);

            // 2. Проверка размера через обход
            traverse_counter = 0;
            ppMap_traverse((ppMap*)&map, count_callback);
            if (traverse_counter != ppMap_size((ppMap*)&map)) {
                printf("ERROR: traverse count %zu != size %u at step %d\n",
                       traverse_counter, ppMap_size((ppMap*)&map), i+1);
                errors++;
            }

            // 3. Дополнительная проверка: для каждого ключа find возвращает правильное значение?
            // Для случайной выборки это сложно, но можно пропустить.
        }
    }

    // Финальная очистка
    ppMap_clear((ppMap*)&map);
    if (!ppMap_empty((ppMap*)&map)) {
        printf("ERROR: map not empty after clear\n");
        errors++;
    }

    printf("Stress test completed with %d errors.\n", errors);
    return errors;
}