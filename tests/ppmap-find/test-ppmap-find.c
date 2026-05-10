// test-ppmap-find.c - тестирование поиска в обобщённом отображении ppMap
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

//------------------------------------------------------------------------------
// Обработчик вывода
void ppMap_element_print<ppMap.IntPair* m>(FILE* f) {
  fprintf(f, "%d->%d ", m->@.key, m->@.value);
}

//------------------------------------------------------------------------------
int main(void) {
  int errors = 0;
  printf("\n-------------------------------------------\n");
  printf("FIND\n\n");

  ppMap_VAR(IntPair, map);
  ppMap_init((ppMap*)&map, cmp_int);

  // Подготовка данных: вставляем несколько пар
  int keys[] = {10, 20, 30, 40, 50};
  int vals[] = {100, 200, 300, 400, 500};
  for (int i = 0; i < 5; i++) {
    ppMap_INSERT(map, keys[i], vals[i]);
  }
  print_map((ppMap*)&map, "initial map");

  // 1. Поиск существующего ключа
  printf("\nTest 1: Find existing keys\n");
  int found_val;
  for (int i = 0; i < 5; i++) {
    if (ppMap_FIND(map, keys[i], found_val)) {
      char msg[64];
      sprintf(msg, "key %d found, value = %d", keys[i], found_val);
      check_condition(found_val == vals[i], msg, &errors);
    } else {
      char msg[64];
      sprintf(msg, "key %d NOT found (should exist)", keys[i]);
      check_condition(0, msg, &errors);
    }
  }

  // 2. Поиск отсутствующего ключа
  printf("\nTest 2: Find non-existing keys\n");
  int missing_keys[] = {5, 15, 25, 35, 45, 55};
  for (int i = 0; i < 6; i++) {
    int result = ppMap_FIND(map, missing_keys[i], found_val);
    char msg[64];
    sprintf(msg, "key %d not found (returns 0, value unchanged)", missing_keys[i]);
    check_condition(result == 0, msg, &errors);
    // Также проверяем, что found_val стал 0 (макрос обнуляет)
    check_condition(found_val == 0, "found_val set to 0", &errors);
  }

  // 3. Поиск после вставки новых элементов
  printf("\nTest 3: Find after inserting more elements\n");
  ppMap_INSERT(map, 60, 600);
  ppMap_INSERT(map, 70, 700);
  if (ppMap_FIND(map, 60, found_val)) {
    check_condition(found_val == 600, "new key 60 found", &errors);
  } else {
    check_condition(0, "new key 60 not found", &errors);
  }
  if (ppMap_FIND(map, 70, found_val)) {
    check_condition(found_val == 700, "new key 70 found", &errors);
  } else {
    check_condition(0, "new key 70 not found", &errors);
  }

  // 4. Поиск после удаления элемента
  printf("\nTest 4: Find after erase\n");
  ppMap_ERASE(map, 40);
  int result = ppMap_FIND(map, 40, found_val);
  check_condition(result == 0, "key 40 no longer exists", &errors);
  check_condition(found_val == 0, "found_val set to 0", &errors);

  // 5. Поиск в пустом отображении
  printf("\nTest 5: Find in empty map\n");
  ppMap_clear((ppMap*)&map);
  result = ppMap_FIND(map, 10, found_val);
  check_condition(result == 0, "empty map returns 0", &errors);
  check_condition(found_val == 0, "found_val = 0", &errors);

  printf("\n-------------------------------------------\n");
  printf("Total errors: %d\n", errors);
  return errors;
}