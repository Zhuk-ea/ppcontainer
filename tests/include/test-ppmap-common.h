#ifndef TEST_PPMAP_COMMON_H
#define TEST_PPMAP_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmap.h"

//==============================================================================
// Вспомогательные функции для сбора данных из отображения (через обход)
//==============================================================================


static void* node_key(ppMapNode* node) { return node->data; }
static void* node_value(ppMap* map, ppMapNode* node) { return node->data + map->key_size; }


// Структура для сбора ключей при обходе
typedef struct {
    void* buffer;   // указатель на массив (например, int*)
    size_t capacity;
    size_t size;
    size_t elem_size;
} MapCollector;

// Callback для сбора ключей
static void collect_keys_callback(void* key, void* value, void* user_data) {
    MapCollector* coll = (MapCollector*)user_data;
    if (coll->size < coll->capacity) {
        memcpy((char*)coll->buffer + coll->size * coll->elem_size, key, coll->elem_size);
        coll->size++;
    }
}

// Callback для сбора значений
static void collect_values_callback(void* key, void* value, void* user_data) {
    MapCollector* coll = (MapCollector*)user_data;
    if (coll->size < coll->capacity) {
        memcpy((char*)coll->buffer + coll->size * coll->elem_size, value, coll->elem_size);
        coll->size++;
    }
}

// Получить массив ключей в порядке возрастания (память выделяется malloc)
// elem_size – размер одного ключа (обычно sizeof(int))
void* ppMap_collect_keys(ppMap* m, size_t* out_count, size_t elem_size) {
    size_t n = ppMap_size(m);
    void* arr = malloc(n * elem_size);
    if (!arr) return NULL;
    MapCollector coll = { arr, n, 0, elem_size };
    ppMap_traverse_with_data(m, collect_keys_callback, &coll);
    *out_count = coll.size;
    return arr;
}

// Получить массив значений в порядке возрастания ключей
void* ppMap_collect_values(ppMap* m, size_t* out_count, size_t elem_size) {
    size_t n = ppMap_size(m);
    void* arr = malloc(n * elem_size);
    if (!arr) return NULL;
    MapCollector coll = { arr, n, 0, elem_size };
    ppMap_traverse_with_data(m, collect_values_callback, &coll);
    *out_count = coll.size;
    return arr;
}

//==============================================================================
// Функция проверки содержимого отображения для типа int
//==============================================================================
void check_map_int_content(ppMap* m, int* expected_keys, int* expected_vals, size_t n,
                           int* errors, const char* msg) {
    size_t size = ppMap_size(m);
    if (size != n) {
        printf("Incorrect | %s: size mismatch (got %zu, expected %zu)\n", msg, size, n);
        (*errors)++;
        return;
    }
    size_t collected_keys_n = 0, collected_vals_n = 0;
    int* keys = (int*)ppMap_collect_keys(m, &collected_keys_n, sizeof(int));
    int* vals = (int*)ppMap_collect_values(m, &collected_vals_n, sizeof(int));
    int ok = 1;
    if (collected_keys_n != n || collected_vals_n != n) ok = 0;
    for (size_t i = 0; ok && i < n; ++i) {
        if (keys[i] != expected_keys[i] || vals[i] != expected_vals[i]) ok = 0;
    }
    if (ok)
        printf("Correct | %s\n", msg);
    else {
        printf("Incorrect | %s\n", msg);
        (*errors)++;
    }
    free(keys);
    free(vals);
}

//==============================================================================
// Вспомогательная печать отображения
//==============================================================================
void print_map(ppMap* m, const char* name) {
    printf("%s: ", name);
    ppMap_print(stdout, m);
}

//==============================================================================
// Компаратор для int (удобно использовать в тестах)
//==============================================================================
static int cmp_int(const void* a, const void* b) {
    int ia = *(int*)a, ib = *(int*)b;
    return (ia > ib) - (ia < ib);
}

//==============================================================================
// Функция проверки свойств красно-чёрного дерева (рекурсивная)
// Возвращает чёрную высоту поддерева, или -1 при нарушении.
// Также увеличивает счетчик errors при любом нарушении.
//==============================================================================
static int check_rb_node(ppMapNode* node, int* black_height, int* errors, int depth) {
    if (node == NULL) {
        *black_height = 0;
        return 1;
    }
    // Проверка: красный узел не может иметь красных детей
    if (node->color == 1) { // RED
        if ((node->left && node->left->color == 1) ||
            (node->right && node->right->color == 1)) {
            printf("RB violation at depth %d: RED node (key=%d) has RED child\n", 
                   depth, *(int*)node_key(node));
            (*errors)++;
            return 0;
        }
        // Также проверим, что родитель не красный (избыточно, но для полноты)
        if (node->parent && node->parent->color == 1) {
            printf("RB violation at depth %d: RED node (key=%d) has RED parent\n", 
                   depth, *(int*)node_key(node));
            (*errors)++;
            return 0;
        }
    }
    int left_h, right_h;
    int left_ok = check_rb_node(node->left, &left_h, errors, depth+1);
    int right_ok = check_rb_node(node->right, &right_h, errors, depth+1);
    if (!left_ok || !right_ok) return 0;
    if (left_h != right_h) {
        printf("RB violation at node key=%d: black height left=%d, right=%d\n",
               *(int*)node_key(node), left_h, right_h);
        (*errors)++;
        return 0;
    }
    *black_height = left_h + (node->color == 0 ? 1 : 0);
    return 1;
}

void ppMap_check_rb_properties(ppMap* m, int* errors) {
    if (m->root == NULL) {
        printf("Tree is empty, no properties to check.\n");
        return;
    }
    if (m->root->color != 0) {
        printf("RB violation: root (key=%d) is not black\n", *(int*)node_key(m->root));
        (*errors)++;
    }
    int black_height;
    if (!check_rb_node(m->root, &black_height, errors, 0)) {
        printf("RB properties check failed.\n");
    } else {
        printf("RB properties OK (black height = %d)\n", black_height);
    }
}

//==============================================================================
// Универсальная функция проверки условия
//==============================================================================
void test_check_condition(int condition, const char* msg, int* errors) {
    if (condition) printf("Correct | %s\n", msg);
    else { printf("Incorrect | %s\n", msg); (*errors)++; }
}


static void print_tree_rec(ppMapNode* node, int depth, int is_left) {
    if (node == NULL) {
        for (int i = 0; i < depth; ++i) printf("    ");
        printf("NULL (black)\n");
        return;
    }
    for (int i = 0; i < depth; ++i) printf("    ");
    printf("%d(%s) ", *(int*)node_key(node), node->color ? "RED" : "BLK");
    if (is_left == 1) printf(" (L)\n");
    else if (is_left == 0) printf(" (R)\n");
    else printf("\n");
    print_tree_rec(node->left, depth+1, 1);
    print_tree_rec(node->right, depth+1, 0);
}

void ppMap_print_tree(ppMap* m, const char* msg) {
    printf("%s:\n", msg);
    print_tree_rec(m->root, 0, -1);
    printf("\n");
}

#endif // TEST_PPMAP_COMMON_H