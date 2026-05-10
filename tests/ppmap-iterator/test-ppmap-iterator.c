// test-ppmap-iterator.c - тестирование итераторов для обобщённого отображения ppMap
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
ppMapRIterator+<IntPair;>;

//------------------------------------------------------------------------------
// Обработчик вывода (для отладочной печати)
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}


//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n\n");

  ppMap_VAR(IntPair, map, cmp_int);
  ppMapIterator_VAR(IntPair, it);
  ppMapRIterator_VAR(IntPair, rit);
  int key, val;

  // 1. BEGIN
  printf("BEGIN\n\n");

  // 1.1 Пустое отображение
  ppMap_CLEAR(map);
  printf("Test 1.1: begin on empty map\n");
  ppMap_BEGIN(map, it);
  test_check_condition(it.node == NULL, "iterator node is NULL", &errors);
  printf("\n");

  // 1.2 Один элемент
  ppMap_CLEAR(map);
  ppMap_INSERT(map, 99, 999);
  printf("Test 1.2: begin on single-element map\n");
  print_map((ppMap*)&map, "map");
  ppMap_BEGIN(map, it);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 99 && val == 999, "key=99, value=999", &errors);
  printf("\n");

  // 1.3 Несколько элементов
  int keys1[] = {50, 20, 70, 10, 30};
  int vals1[] = {500, 200, 700, 100, 300};
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5);
  printf("Test 1.3: begin on multi-element map\n");
  print_map((ppMap*)&map, "map");
  ppMap_BEGIN(map, it);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 10 && val == 100, "min key = 10, value = 100", &errors);
  printf("\n-------------------------------------------\n\n");

  // 2. END
  printf("END\n\n");

  // 2.1 Пустое отображение
  ppMap_CLEAR(map);
  printf("Test 2.1: end on empty map\n");
  ppMap_END(map, it);
  test_check_condition(it.node == NULL, "iterator node is NULL", &errors);
  printf("\n");

  // 2.2 Один элемент
  ppMap_CLEAR(map);
  ppMap_INSERT(map, 42, 4242);
  printf("Test 2.2: end on single-element map\n");
  print_map((ppMap*)&map, "map");
  ppMap_END(map, it);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 42 && val == 4242, "key=42, value=4242", &errors);
  printf("\n");

  // 2.3 Несколько элементов (восстанавливаем те же ключи, что в 1.3)
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5);
  printf("Test 2.3: end on multi-element map\n");
  print_map((ppMap*)&map, "map");
  ppMap_END(map, it);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 70 && val == 700, "max key = 70, value = 700", &errors);
  printf("\n-------------------------------------------\n\n");

  // 3. RBEGIN / REND
  printf("RBEGIN / REND\n\n");

  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5);
  printf("Test 3.1: rbegin points to max key\n");
  ppMap_RBEGIN(map, rit);
  ppMapRIterator_GET_KEY(key, rit);
  ppMapRIterator_GET_VALUE(val, rit);
  test_check_condition(key == 70 && val == 700, "rbegin -> 70->700", &errors);
  printf("\n");

  printf("Test 3.2: rend points to min key\n");
  ppMap_REND(map, rit);
  ppMapRIterator_GET_KEY(key, rit);
  ppMapRIterator_GET_VALUE(val, rit);
  test_check_condition(key == 10 && val == 100, "rend -> 10->100", &errors);
  printf("\n-------------------------------------------\n\n");

  // 4. ITERATOR NEXT
  printf("ITERATOR NEXT\n\n");

  // 4.1 Итератор на NULL
  ppMap_CLEAR(map);
  it.map = (ppMap*)&map;
  it.node = NULL;
  printf("Test 4.1: next on NULL iterator\n");
  _Bool res = ppMapIterator_NEXT(it);
  test_check_condition(res == 0 && it.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 4.2 Один элемент: next переводит на NULL, возвращает 1
  ppMap_CLEAR(map);
  ppMap_INSERT(map, 5, 55);
  ppMap_BEGIN(map, it);
  printf("Test 4.2: next on single-element -> NULL\n");
  print_map((ppMap*)&map, "map");
  res = ppMapIterator_NEXT(it);
  test_check_condition(res == 1 && it.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 4.3 Несколько элементов: проход до NULL
  int keysA[] = {10,20,30,40};
  int valsA[] = {100,200,300,400};
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keysA, valsA, 4);
  ppMap_BEGIN(map, it);
  printf("Test 4.3: next through all elements\n");
  print_map((ppMap*)&map, "map");
  res = ppMapIterator_NEXT(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 20, "next -> 20, returns 1", &errors);
  res = ppMapIterator_NEXT(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 30, "next -> 30, returns 1", &errors);
  res = ppMapIterator_NEXT(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 40, "next -> 40, returns 1", &errors);
  res = ppMapIterator_NEXT(it);
  test_check_condition(res == 1 && it.node == NULL, "next -> NULL, returns 1", &errors);
  res = ppMapIterator_NEXT(it);
  test_check_condition(res == 0 && it.node == NULL, "next on NULL -> 0", &errors);
  printf("\n-------------------------------------------\n\n");

  // 5. ITERATOR PREV
  printf("ITERATOR PREV\n\n");

  // 5.1 Итератор на NULL
  it.node = NULL;
  printf("Test 5.1: prev on NULL iterator\n");
  res = ppMapIterator_PREV(it);
  test_check_condition(res == 0 && it.node == NULL, "returns 0, node stays NULL", &errors);
  printf("\n");

  // 5.2 Один элемент: prev переводит на NULL, возвращает 1
  ppMap_CLEAR(map);
  ppMap_INSERT(map, 7, 77);
  ppMap_END(map, it);
  printf("Test 5.2: prev on single-element -> NULL\n");
  print_map((ppMap*)&map, "map");
  res = ppMapIterator_PREV(it);
  test_check_condition(res == 1 && it.node == NULL, "returns 1, node becomes NULL", &errors);
  printf("\n");

  // 5.3 Несколько элементов: prev от конца до NULL
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keysA, valsA, 4);
  ppMap_END(map, it);
  printf("Test 5.3: prev through all elements\n");
  print_map((ppMap*)&map, "map");
  res = ppMapIterator_PREV(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 30, "prev -> 30, returns 1", &errors);
  res = ppMapIterator_PREV(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 20, "prev -> 20, returns 1", &errors);
  res = ppMapIterator_PREV(it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(res == 1 && key == 10, "prev -> 10, returns 1", &errors);
  res = ppMapIterator_PREV(it);
  test_check_condition(res == 1 && it.node == NULL, "prev -> NULL, returns 1", &errors);
  res = ppMapIterator_PREV(it);
  test_check_condition(res == 0 && it.node == NULL, "prev on NULL -> 0", &errors);
  printf("\n-------------------------------------------\n\n");

  // 6. REVERSE ITERATOR NEXT
  printf("REVERSE ITERATOR NEXT\n\n");

  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keysA, valsA, 4);
  ppMap_RBEGIN(map, rit);
  printf("Test 6.1: reverse next moves to smaller keys\n");
  print_map((ppMap*)&map, "map");
  res = ppMapRIterator_NEXT(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 30, "reverse next -> 30", &errors);
  res = ppMapRIterator_NEXT(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 20, "reverse next -> 20", &errors);
  res = ppMapRIterator_NEXT(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 10, "reverse next -> 10", &errors);
  res = ppMapRIterator_NEXT(rit);
  test_check_condition(res == 1 && rit.node == NULL, "reverse next -> NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  // 7. REVERSE ITERATOR PREV
  printf("REVERSE ITERATOR PREV\n\n");
  ppMap_REND(map, rit);
  res = ppMapRIterator_PREV(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 20, "reverse prev -> 20", &errors);
  res = ppMapRIterator_PREV(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 30, "reverse prev -> 30", &errors);
  res = ppMapRIterator_PREV(rit);
  ppMapRIterator_GET_KEY(key, rit);
  test_check_condition(res == 1 && key == 40, "reverse prev -> 40", &errors);
  res = ppMapRIterator_PREV(rit);
  test_check_condition(res == 1 && rit.node == NULL, "reverse prev -> NULL", &errors);
  printf("\n-------------------------------------------\n\n");

  //  8. GET_KEY / GET_VALUE не двигают итератор
  printf("GET_VALUE / GET_KEY no move\n\n");
  ppMap_CLEAR(map);
  ppMap_INSERT(map, 123, 456);
  ppMap_BEGIN(map, it);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 123 && val == 456, "first read", &errors);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 123 && val == 456, "second read same values (iterator unchanged)", &errors);
  printf("\n-------------------------------------------\n\n");

  //  9. ERASE ITERATOR
  printf("ERASE ITERATOR\n\n");

  // 9.1 Удаление корня (30)
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5);
  printf("Test 9.1: erase root (30)\n");
  print_map((ppMap*)&map, "map");

  ppMap_BEGIN(map, it);
  while (it.node != NULL) {
    ppMapIterator_GET_KEY(key, it);
    if (key == 30) break;
    ppMapIterator_NEXT(it);
  }
  res = ppMapIterator_ERASE(it);
  test_check_condition(res == 1, "erase returns 1", &errors);
  int found_val;
  _Bool found = ppMap_FIND(map, 30, found_val);
  test_check_condition(!found, "key 30 no longer exists", &errors);
  print_map((ppMap*)&map, "map");
  printf("\n");

  // 9.2 Удаление листа (10)
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keysA, valsA, 4);
  printf("Test 9.2: erase leaf (10)\n");
  print_map((ppMap*)&map, "map");
  ppMap_BEGIN(map, it); 
  res = ppMapIterator_ERASE(it);
  test_check_condition(res == 1, "erase returns 1", &errors);
  found = ppMap_FIND(map, 10, found_val);
  test_check_condition(!found, "key 10 no longer exists", &errors);
  print_map((ppMap*)&map, "map");
  printf("\n");

  // 9.3 Попытка удаления по невалидному итератору
  printf("Test 9.3: erase on NULL iterator\n");
  it.node = NULL;
  res = ppMapIterator_ERASE(it);
  test_check_condition(res == 0, "returns 0", &errors);
  printf("\n");

  // 9.4 Удаление всех элементов по одному через итератор (корректный способ)
  printf("Test 9.4: erase all elements via iterator\n");
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keysA, valsA, 4);

  while (!ppMap_empty((ppMap*)&map)) {
    ppMap_BEGIN(map, it);
    ppMapIterator_ERASE(it);
  }
  test_check_condition(ppMap_empty((ppMap*)&map) == 1, "map becomes empty after erasing all", &errors);
  printf("\n-------------------------------------------\n\n");

  // 10. FIND_ITERATOR
  printf("FIND_ITERATOR\n\n");

  // 10.1 Поиск существующего ключа
  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5); // 10,20,30,50,70
  printf("Test 10.1: find_iterator on existing key 30\n");
  res = ppMap_FIND_ITERATOR(map, 30, it);
  test_check_condition(res, "find_iterator returns 1", &errors);
  ppMapIterator_GET_KEY(key, it);
  ppMapIterator_GET_VALUE(val, it);
  test_check_condition(key == 30 && val == 300, "iterator points to 30->300", &errors);
  printf("\n");

  // 10.2 Поиск отсутствующего ключа
  printf("Test 10.2: find_iterator on non-existing key 35\n");
  res = ppMap_FIND_ITERATOR(map, 35, it);
  test_check_condition(!res, "find_iterator returns 0", &errors);
  // Итератор должен указывать на end() (максимальный элемент 70)
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 70, "iterator set to end() (max element 70)", &errors);
  printf("\n");

  // 10.3 Поиск в пустом отображении
  printf("Test 10.3: find_iterator on empty map\n");
  ppMap_CLEAR(map);
  res = ppMap_FIND_ITERATOR(map, 10, it);
  test_check_condition(!res, "returns 0", &errors);
  test_check_condition(it.node == NULL, "iterator is end()", &errors);
  printf("\n-------------------------------------------\n\n");

  // 11. LOWER_BOUND
  printf("LOWER_BOUND\n\n");

  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5); // 10,20,30,50,70

  // 11.1 lower_bound на существующий ключ
  printf("Test 11.1: lower_bound(30)\n");
  ppMap_LOWER_BOUND(map, 30, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 30, "returns iterator to 30", &errors);
  printf("\n");

  // 11.2 lower_bound на ключ между существующими
  printf("Test 11.2: lower_bound(25)\n");
  ppMap_LOWER_BOUND(map, 25, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 30, "returns iterator to 30 (first >= 25)", &errors);
  printf("\n");

  // 11.3 lower_bound на ключ меньше минимального
  printf("Test 11.3: lower_bound(5)\n");
  ppMap_LOWER_BOUND(map, 5, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 10, "returns iterator to 10 (first >= 5)", &errors);
  printf("\n");

  // 11.4 lower_bound на ключ больше максимального
  printf("Test 11.4: lower_bound(75)\n");
  ppMap_LOWER_BOUND(map, 75, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 70, "returns end() (max element 70)", &errors);
  printf("\n");

  // 11.5 lower_bound на пустом отображении
  printf("Test 11.5: lower_bound on empty map\n");
  ppMap_CLEAR(map);
  ppMap_LOWER_BOUND(map, 10, it);
  test_check_condition(it.node == NULL, "returns end()", &errors);
  printf("\n-------------------------------------------\n\n");

  // 12. UPPER_BOUND
  printf("UPPER_BOUND\n\n");

  ppMap_CLEAR(map);
  ppMap_FILL_FROM_ARRAYS(map, keys1, vals1, 5); // 10,20,30,50,70

  // 12.1 upper_bound на существующий ключ
  printf("Test 12.1: upper_bound(30)\n");
  ppMap_UPPER_BOUND(map, 30, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 50, "returns iterator to 50 (first > 30)", &errors);
  printf("\n");

  // 12.2 upper_bound на ключ между существующими
  printf("Test 12.2: upper_bound(25)\n");
  ppMap_UPPER_BOUND(map, 25, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 30, "returns iterator to 30 (first > 25)", &errors);
  printf("\n");

  // 12.3 upper_bound на ключ меньше минимального
  printf("Test 12.3: upper_bound(5)\n");
  ppMap_UPPER_BOUND(map, 5, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 10, "returns iterator to 10 (first > 5)", &errors);
  printf("\n");

  // 12.4 upper_bound на ключ больше максимального
  printf("Test 12.4: upper_bound(75)\n");
  ppMap_UPPER_BOUND(map, 75, it);
  ppMapIterator_GET_KEY(key, it);
  test_check_condition(key == 70, "returns end() (max element 70)", &errors);
  printf("\n");

  // 12.5 upper_bound на пустом отображении
  printf("Test 12.5: upper_bound on empty map\n");
  ppMap_CLEAR(map);
  ppMap_UPPER_BOUND(map, 10, it);
  test_check_condition(it.node == NULL, "returns end()", &errors);
  printf("\n-------------------------------------------\n\n");

  printf("Total errors: %d\n", errors);
  return errors;
}