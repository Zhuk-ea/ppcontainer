// ppmap.c - определения функций для обобщенного отображения (красно-чёрное дерево)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ppmap.h"

#define RED  1
#define BLACK 0

//------------------------------------------------------------------------------
// Вспомогательные функции для доступа к ключу и значению узла
static void* node_key(ppMapNode* node) { return node->data; }
static void* node_value(ppMap* map, ppMapNode* node) { return node->data + map->key_size; }

//------------------------------------------------------------------------------
// Вспомогательная функция создания нового узла
// Новый узел всегда красный.
static ppMapNode* new_node(ppMap* map) {
  ppMapNode* node = (ppMapNode*)malloc(sizeof(ppMapNode) + map->foundation_size);
  if (!node) { 
    fprintf(stderr, "Memory allocation failed\n"); 
    exit(-1);
  }
  memcpy(node->data, map->foundation_addr, map->foundation_size);
  node->left = node->right = node->parent = NULL;
  node->color = RED;
  return node;
}

static void free_node(ppMapNode* node) { free(node); }

//------------------------------------------------------------------------------
// Вспомогательные функции проверки цвета узла (учитывая NULL как чёрный)
static int is_red(ppMapNode* node) { return node != NULL && node->color == RED; }
static int is_black(ppMapNode* node) { return node == NULL || node->color == BLACK; }

//------------------------------------------------------------------------------
// Вспомогательная функция левого поворота вокруг узла x
static void rotate_left(ppMap* map, ppMapNode* x) {
  if (!x || !x->right) { return; }
  ppMapNode* y = x->right;
  // Перемещаем левое поддерево y в правое поддерево x
  x->right = y->left;
  if (y->left != NULL) y->left->parent = x;
  // Поднимаем y на место x
  y->parent = x->parent;
  if (x->parent == NULL) map->root = y;
  else if (x == x->parent->left) x->parent->left = y;
  else x->parent->right = y;
  // Делаем x левым ребёнком y
  y->left = x;
  x->parent = y;
}

//------------------------------------------------------------------------------
// Вспомогательная функция правого поворота вокруг узла y
static void rotate_right(ppMap* map, ppMapNode* y) {
  if (!y || !y->left) { return; }
  ppMapNode* x = y->left;
  // Перемещаем правое поддерево x в левое поддерево y
  y->left = x->right;
  if (x->right != NULL) x->right->parent = y;
  // Поднимаем x на место y
  x->parent = y->parent;
  if (y->parent == NULL) map->root = x;
  else if (y == y->parent->left) y->parent->left = x;
  else y->parent->right = x;
  // Делаем y правым ребёнком x
  x->right = y;
  y->parent = x;
}

//------------------------------------------------------------------------------
// Вспомогательная функция восстановления свойств красно-чёрного дерева после вставки
static void fix_insert(ppMap* map, ppMapNode* z) {
  // Пока родитель красный, нарушение свойств
  while (z->parent != NULL && is_red(z->parent)) {
    if (z->parent == z->parent->parent->left) { // родитель - левый ребёнок
      ppMapNode* y = z->parent->parent->right; // дядя
      if (is_red(y)) {
        // Случай 1: дядя красный - перекрашиваем
        z->parent->color = BLACK;
        if (y) y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent; // поднимаемся вверх
      } else {
        // Случай 2: дядя чёрный
        if (z == z->parent->right) {
          // Треугольник: большой поворот
          z = z->parent;
          rotate_left(map, z);
        }
        // Случай 3: линия - перекраска и правый поворот
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotate_right(map, z->parent->parent);
      }
    } else { // родитель - правый ребёнок, симметрично
      ppMapNode* y = z->parent->parent->left;
      if (is_red(y)) {
        z->parent->color = BLACK;
        if (y) y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotate_right(map, z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotate_left(map, z->parent->parent);
      }
    }
  }
  // Корень всегда чёрный
  map->root->color = BLACK;
}

//------------------------------------------------------------------------------
// Вставка элемента в map
// Если ключ уже существует, заменяет значение
void ppMap_insert(ppMap* map) {
  if (!map->cmp) {
    fprintf(stderr, "Comparator not set\n");
    exit(-1);
  }
  ppMapNode* z = new_node(map);
  // Пустое дерево
  if (map->root == NULL) {
    map->root = z;
    map->root->color = BLACK;
    map->size = 1;
    return;
  }
  // Поиск места для вставки
  ppMapNode* y = NULL;
  ppMapNode* x = map->root;
  void* key_z = node_key(z);
  while (x != NULL) {
    y = x;
    int cmp = map->cmp(key_z, node_key(x));
    if (cmp < 0) x = x->left;
    else if (cmp > 0) x = x->right;
    else {
      // Ключ уже существует - обновляем значение
      memcpy(node_value(map, x), node_value(map, z), map->value_size);
      free_node(z);
      return;
    }
  }
  // Вставка нового узла
  z->parent = y;
  if (map->cmp(key_z, node_key(y)) < 0) y->left = z;
  else y->right = z;
  fix_insert(map, z);
  map->size++;
}

//------------------------------------------------------------------------------
// Поиск узла по ключу, занесённому в специализацию
// Возвращает указатель на найденный узел или NULL
static ppMapNode* find_node(ppMap* map) {
  if (map->root == NULL) return NULL;
  void* target = map->foundation_addr;
  ppMapNode* cur = map->root;
  while (cur) {
    int cmp = map->cmp(target, node_key(cur));
    if (cmp < 0) cur = cur->left;
    else if (cmp > 0) cur = cur->right;
    else return cur; // найден
  }
  return NULL;
}

//------------------------------------------------------------------------------
// Поиск значения по ключу.
// Возвращает 1, если ключ найден, и копирует значение в специализацию
_Bool ppMap_find(ppMap* map) {
  ppMapNode* n = find_node(map);
  if (!n) return 0;
  // Копируем значение в область специализации
  memcpy(map->foundation_addr + map->key_size, node_value(map, n), map->value_size);
  return 1;
}

//------------------------------------------------------------------------------
// Вспомогательная функция, возвращает узел с минимальным ключом в поддереве x
static ppMapNode* tree_minimum(ppMapNode* x) {
  while (x && x->left) x = x->left;
  return x;
}

//------------------------------------------------------------------------------
// Вспомогательная функция замены поддерева с корнем u на поддерево с корнем v
static void transplant(ppMap* map, ppMapNode* u, ppMapNode* v) {
  if (u->parent == NULL) map->root = v;
  else if (u == u->parent->left) u->parent->left = v;
  else u->parent->right = v;
  if (v != NULL) v->parent = u->parent;
}

//------------------------------------------------------------------------------
// Вспомогательная функция восстановления свойств красно-чёрного дерева после удаления
static void fix_delete(ppMap* map, ppMapNode* x, ppMapNode* parent) {
  // Продолжаем, пока x не корень и x чёрный (NULL считается чёрным)
  while ((x != NULL ? x : parent) != map->root && is_black(x)) {
    if (x == NULL) {
      // Случай, когда x - NULL-лист, определяем его сторону относительно parent
      if (parent->left == NULL) { // x - левый ребёнок
        ppMapNode* w = parent->right; // брат
        if (is_red(w)) { // Случай 1: брат красный - перекрашиваем и поворачиваем
          w->color = BLACK;
          parent->color = RED;
          rotate_left(map, parent);
          w = parent->right;
        }
        if (is_black(w->left) && is_black(w->right)) { // Случай 2: оба племянника чёрные - перекрашиваем брата и поднимаемся
          w->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          // Случай 3: правый племянник чёрный - перекрашиваем и поворачиваем
          if (is_black(w->right)) {
            w->left->color = BLACK;
            w->color = RED;
            rotate_right(map, w);
            w = parent->right;
          }
          // Случай 4: левый племянник чёрный - перекраска и левый поворот
          w->color = parent->color;
          parent->color = BLACK;
          w->right->color = BLACK;
          rotate_left(map, parent);
          x = map->root;
          parent = NULL;
        }
      } else { // x - правый ребёнок, симметрично
        ppMapNode* w = parent->left;
        if (is_red(w)) {
          w->color = BLACK;
          parent->color = RED;
          rotate_right(map, parent);
          w = parent->left;
        }
        if (is_black(w->right) && is_black(w->left)) {
          w->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (is_black(w->left)) {
            w->right->color = BLACK;
            w->color = RED;
            rotate_left(map, w);
            w = parent->left;
          }
          w->color = parent->color;
          parent->color = BLACK;
          w->left->color = BLACK;
          rotate_right(map, parent);
          x = map->root;
          parent = NULL;
        }
      }
    } else { // x не NULL, используем стандартный алгоритм
      parent = x->parent;
      if (x == parent->left) {
        ppMapNode* w = parent->right;
        if (is_red(w)) {
          w->color = BLACK;
          parent->color = RED;
          rotate_left(map, parent);
          w = parent->right;
        }
        if (is_black(w->left) && is_black(w->right)) {
          w->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (is_black(w->right)) {
            w->left->color = BLACK;
            w->color = RED;
            rotate_right(map, w);
            w = parent->right;
          }
          w->color = parent->color;
          parent->color = BLACK;
          w->right->color = BLACK;
          rotate_left(map, parent);
          x = map->root;
          parent = NULL;
        }
      } else {
        ppMapNode* w = parent->left;
        if (is_red(w)) {
          w->color = BLACK;
          parent->color = RED;
          rotate_right(map, parent);
          w = parent->left;
        }
        if (is_black(w->right) && is_black(w->left)) {
          w->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (is_black(w->left)) {
            w->right->color = BLACK;
            w->color = RED;
            rotate_left(map, w);
            w = parent->left;
          }
          w->color = parent->color;
          parent->color = BLACK;
          w->left->color = BLACK;
          rotate_right(map, parent);
          x = map->root;
          parent = NULL;
        }
      }
    }
  }
  // Гарантируем, что последний x (если не NULL) становится чёрным
  if (x) x->color = BLACK;
}

//------------------------------------------------------------------------------
// Удаление элемента по ключу (ключ берётся из специализации)
// Возвращает 1, если элемент был удалён, иначе 0
_Bool ppMap_erase(ppMap* map) {
  ppMapNode* z = find_node(map);
  if (!z) return 0;

  ppMapNode* y = z;
  ppMapNode* x = NULL;
  ppMapNode* x_parent = NULL;
  int y_original_color = y->color;

  if (z->left == NULL) {       // Случай 1: удаляемый узел не имеет левого ребёнка
    x = z->right;
    x_parent = z->parent;
    transplant(map, z, z->right);
  }
  else if (z->right == NULL) {    // Случай 2: нет правого ребёнка
    x = z->left;
    x_parent = z->parent;
    transplant(map, z, z->left);
  }
  else {               // Случай 3: два ребёнка - находим преемника
    y = tree_minimum(z->right);  // наименьший в правом поддереве
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x_parent = y;
    } else {
      x_parent = y->parent;
      transplant(map, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(map, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
    if (x) x_parent = x->parent;
  }

  // Если удалённый узел был чёрным, требуется балансировка
  if (y_original_color == BLACK) {
    fix_delete(map, x, x_parent);
  }

  free_node(z);
  map->size--;
  return 1;
}

//------------------------------------------------------------------------------
// Вспомогательная функция рекурсивного освобождения памяти поддерева
static void clear_rec(ppMapNode* node) {
  if (!node) return;
  clear_rec(node->left);
  clear_rec(node->right);
  free(node);
}

//------------------------------------------------------------------------------
// Очистка map
void ppMap_clear(ppMap* map) {
  clear_rec(map->root);
  map->root = NULL;
  map->size = 0;
}

//------------------------------------------------------------------------------
// Вспомогательная функция рекурсивного обхода в порядке возрастания (простой callback)
static void traverse_rec_simple(ppMapNode* node, void (*cb)(void*, void*), ppMap* map) {
  if (!node) return;
  traverse_rec_simple(node->left, cb, map);
  cb(node_key(node), node_value(map, node));
  traverse_rec_simple(node->right, cb, map);
}

//------------------------------------------------------------------------------
// Обход дерева с вызовом функции callback(key, value)
void ppMap_traverse(ppMap* map, void (*cb)(void*, void*)) {
  traverse_rec_simple(map->root, cb, map);
}

//------------------------------------------------------------------------------
// Вспомогательная функция рекурсивного обхода с пользовательскими данными
static void traverse_rec_with_data(ppMapNode* node, void (*cb)(void*, void*, void*), void* data, ppMap* map) {
  if (!node) return;
  traverse_rec_with_data(node->left, cb, data, map);
  cb(node_key(node), node_value(map, node), data);
  traverse_rec_with_data(node->right, cb, data, map);
}

//------------------------------------------------------------------------------
// Обход дерева с вызовом callback(key, value, user_data)
void ppMap_traverse_with_data(ppMap* map, void (*cb)(void*, void*, void*), void* data) {
  traverse_rec_with_data(map->root, cb, data, map);
}

//------------------------------------------------------------------------------
// Инициализация map
void ppMap_init(ppMap* map, int (*cmp)(const void*, const void*)) {
  map->size = 0;
  map->root = NULL;
  map->cmp = cmp;
}

uint32_t ppMap_size(ppMap* map) { return map->size; }
_Bool ppMap_empty(ppMap* map) { return map->size == 0; }

//------------------------------------------------------------------------------
// Структура для передачи данных в callback при сравнении map
typedef struct { ppMap* m2; int equal; } EqData;

//------------------------------------------------------------------------------
// Callback для проверки равенства одного узла
static void check_node_equal(void* key, void* value, void* user_data) {
  EqData* d = (EqData*)user_data;
  if (!d->equal) return;
  // Копируем ключ в основу второго map и выполняем поиск
  memcpy(d->m2->foundation_addr, key, d->m2->key_size);
  if (!ppMap_find(d->m2)) { d->equal = 0; return; }
  // Сравниваем значения
  void* found = d->m2->foundation_addr + d->m2->key_size;
  if (memcmp(found, value, d->m2->value_size) != 0) d->equal = 0;
}

//------------------------------------------------------------------------------
// Сравнение двух map на равенство
_Bool ppMap_is_equal(ppMap* m1, ppMap* m2) {
  if (m1->size != m2->size) return 0;
  EqData data = { m2, 1 };
  ppMap_traverse_with_data(m1, check_node_equal, &data);
  return data.equal;
}

//------------------------------------------------------------------------------
// Быстрый обмен содержимым двух map
void ppMap_swap(ppMap* a, ppMap* b) {
  ppMap tmp = *a;
  *a = *b;
  *b = tmp;
}

//------------------------------------------------------------------------------
// Перемещение данных из src в dest, src становится пустым
void ppMap_move(ppMap* dest, ppMap* src) {
  ppMap_clear(dest);
  dest->root = src->root;
  dest->size = src->size;
  dest->key_size = src->key_size;
  dest->value_size = src->value_size;
  dest->foundation_size = src->foundation_size;
  dest->foundation_addr = src->foundation_addr;
  dest->cmp = src->cmp;
  // Очищаем src, но не вызываем clear (чтобы не освобождать память)
  src->root = NULL;
  src->size = 0;
}

//------------------------------------------------------------------------------
// Структура для передачи данных в callback при копировании
typedef struct { ppMap* dest; } CopyData;

//------------------------------------------------------------------------------
// Callback для копирования одного узла
static void copy_callback(void* key, void* value, void* user_data) {
  CopyData* d = (CopyData*)user_data;
  // Копируем ключ и значение в основу целевого map
  memcpy(d->dest->foundation_addr, key, d->dest->key_size);
  memcpy(d->dest->foundation_addr + d->dest->key_size, value, d->dest->value_size);
  ppMap_insert(d->dest);
}

//------------------------------------------------------------------------------
// Глубокое копирование map src в dest (предыдущее содержимое dest удаляется)
void ppMap_copy(ppMap* dest, ppMap* src) {
  if (dest == src) return;
  ppMap_clear(dest);
  CopyData data = { dest };
  ppMap_traverse_with_data(src, copy_callback, &data);
}

//------------------------------------------------------------------------------
// Проверка наличия ключа в map (без возврата значения)
_Bool ppMap_contains(ppMap* map) {
  return find_node(map) != NULL;
}