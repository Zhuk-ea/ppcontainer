#ifndef __ppmap_data__
#define __ppmap_data__

//==============================================================================
// Структура обобщенного map (отображения "ключ-значение") на основе красно-чёрного дерева
//==============================================================================

// Структура отображения
typedef struct ppMap {
  uint32_t  key_size;                    // размер ключа (байт)
  uint32_t  value_size;                  // размер значения (байт)
  uint32_t  foundation_size;             // общий размер пары (key_size + value_size)
  void*     foundation_addr;             // адрес основы специализации
  uint32_t  size;                        // количество элементов в дереве
  struct ppMapNode* root;                // корень красно-чёрного дерева
  int (*cmp)(const void*, const void*);  // функция сравнения ключей (возвращает <0, 0, >0)
}<> ppMap;

// Узел красно-чёрного дерева
typedef struct ppMapNode {
  struct ppMapNode* left;      // указатель на левого ребёнка
  struct ppMapNode* right;     // указатель на правого ребёнка
  struct ppMapNode* parent;    // указатель на родителя
  uint8_t color;               // 0 = чёрный, 1 = красный
  char data[];                 // точка доступа к данным
} ppMapNode;

//Итератор для map
typedef struct ppMapIterator {
  struct ppMap * map;           // указатель на map с которым связан
  struct ppMapNode* node;        // указатель на элемент в кч-дереве
} <> ppMapIterator;

//Обратный итератор для map
typedef struct ppMapRIterator {
  struct ppMap * map;           // указатель на map с которым связан
  struct ppMapNode* node;        // указатель на элемент в кч-дереве
} <> ppMapRIterator;

#endif // __ppmap_data__