// test-ppmap-erase-range.c - тестирование удаления диапазона итераторами ppMap
#include <stdio.h>
#include "ppmap.h"
#include "test-ppmap-common.h"

//==============================================================================
// Специализация для int -> int
//==============================================================================
typedef struct IntPair {
    int key;
    int value;
} IntPair;

ppMap+<IntPair;>;
ppMapIterator+<IntPair;>;

//------------------------------------------------------------------------------
// Обработчик вывода
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
    fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
int main(void) {
    int errors = 0;
    printf("\n-------------------------------------------\n");
    printf("TEST ppMapIterator_ERASE_RANGE\n\n");

    ppMap_VAR(IntPair, map, cmp_int);
    ppMapIterator_VAR(IntPair, it_begin);
    ppMapIterator_VAR(IntPair, it_end);
    int key, val;
    uint32_t removed;

    int keys_all[] = {10, 20, 30, 40, 50, 60, 70};
    int vals_all[] = {100, 200, 300, 400, 500, 600, 700};

    // 1. Удаление диапазона из середины
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    printf("Initial map: ");
    print_map((ppMap*)&map, "");

    ppMap_FIND_ITERATOR(map, 30, it_begin);
    ppMap_FIND_ITERATOR(map, 60, it_end);
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);

    test_check_condition(removed == 3, "removed 3 elements (30,40,50)", &errors);
    int exp1[] = {10,20,60,70};
    int expv1[] = {100,200,600,700};
    check_map_int_content((ppMap*)&map, exp1, expv1, 4, &errors, "after erase [30,60)");

    ppMapIterator_GET_KEY(key, it_begin);
    test_check_condition(key == 20, "begin moved to predecessor (20)", &errors);
    ppMapIterator_GET_KEY(key, it_end);
    test_check_condition(key == 60, "end unchanged (60)", &errors);
    printf("\n");

    // 2. Удаление с начала
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    ppMap_BEGIN(map, it_begin);
    ppMap_FIND_ITERATOR(map, 40, it_end);
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 3, "removed 10,20,30", &errors);
    int exp2[] = {40,50,60,70};
    int expv2[] = {400,500,600,700};
    check_map_int_content((ppMap*)&map, exp2, expv2, 4, &errors, "after erase [10,40)");
    ppMapIterator_GET_KEY(key, it_begin);
    test_check_condition(key == 40, "begin becomes end (40)", &errors);
    printf("\n");

    // 3. Удаление до конца (end = NULL)
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    ppMap_FIND_ITERATOR(map, 50, it_begin);
    it_end.map = (ppMap*)&map;
    it_end.node = NULL;
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 3, "removed 50,60,70", &errors);
    int exp3[] = {10,20,30,40};
    int expv3[] = {100,200,300,400};
    check_map_int_content((ppMap*)&map, exp3, expv3, 4, &errors, "after erase [50, NULL)");
    ppMapIterator_GET_KEY(key, it_begin);
    test_check_condition(key == 40, "begin moved to predecessor (40)", &errors);
    printf("\n");

    // 4. Удаление всего map
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    ppMap_BEGIN(map, it_begin);
    it_end.node = NULL;
    it_end.map = (ppMap*)&map;
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 7, "removed all 7", &errors);
    test_check_condition(ppMap_empty((ppMap*)&map), "map empty", &errors);
    test_check_condition(it_begin.node == NULL, "begin = NULL", &errors);
    printf("\n");

    // 5. Пустой диапазон
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    ppMap_FIND_ITERATOR(map, 30, it_begin);
    ppMap_FIND_ITERATOR(map, 30, it_end);
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 0, "empty range -> 0", &errors);
    check_map_int_content((ppMap*)&map, keys_all, vals_all, 7, &errors, "map unchanged");
    printf("\n");

    // 6. Некорректные итераторы
    ppMap_CLEAR(map);
    ppMap_FILL_FROM_ARRAYS(map, keys_all, vals_all, 7);
    it_begin.map = NULL;
    it_begin.node = NULL;
    it_end.map = (ppMap*)&map;
    it_end.node = NULL;
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 0, "invalid begin -> 0", &errors);
    check_map_int_content((ppMap*)&map, keys_all, vals_all, 7, &errors, "map unchanged");

    it_begin.map = (ppMap*)&map;
    it_begin.node = map.root;
    it_end.map = NULL;
    removed = ppMapIterator_ERASE_RANGE(it_begin, it_end);
    test_check_condition(removed == 0, "invalid end -> 0", &errors);
    check_map_int_content((ppMap*)&map, keys_all, vals_all, 7, &errors, "map unchanged");
    printf("\n-------------------------------------------\n");

    printf("Total errors: %d\n", errors);
    return errors;
}