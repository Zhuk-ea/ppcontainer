## Библиотека Стандартных Контейнеров для Процедурно-Параметрического Расширения Языка Программирования C

### Установка

Скачайте **ppc_standard_containers_lib_installer.run** из [последнего релиза](https://github.com/Zhuk-ea/ppcontainer/releases/tag/v1.0.1)

Выполните команды:

```bash
chmod +x ppc_standard_containers_lib_installer.run
sudo ./ppc_standard_containers_lib_installer.run
```

Установщик поместит заголовочные файлы в `/usr/local/include/ppc_containers/`, а статическую библиотеку `libppc_standard_containers.a` – в `/usr/local/lib/`.

### Использование

Добавьте в ваш `CMakeLists.txt` следующие строки для подключения библиотеки:

```cmake
find_library(CONTAINERS_LIB ppc_standard_containers PATHS /usr/local/lib)
if(NOT CONTAINERS_LIB)
    message(FATAL_ERROR "Can't find ppc_standart_containers_lib")
endif()

# Подключение заголовков
target_include_directories(my_program PRIVATE /usr/local/include/)

# Линковка (--whole-archive гарантирует включение всех обобщённых функций)
target_link_libraries(
    my_program PRIVATE
    -Wl,--whole-archive
    ${CONTAINERS_LIB}
    -Wl,--no-whole-archive
)
```

В исходном коде подключайте нужные заголовки:

```c
#include <ppc_containers/pplist.h>   // для списка
#include <ppc_containers/ppvector.h> // для вектора
#include <ppc_containers/ppmap.h>    // для отображения
#include <ppc_containers/ppcontainer.h> // для обобщённого контейнера
```

Пример простейшей программы со списком `ppList<int>`:

```c
#include <stdio.h>
#include <ppc_containers/pplist.h>

ppList+<int;>;
void ppList_element_print<ppList.int* l>(FILE* f) {
    fprintf(f, "%d ", l->@);
}

int main() {
    ppList_VAR(int, my_list);
    for (int i = 1; i <= 5; ++i) ppList_PUSH_BACK(my_list, i * 10);
    ppList_print2(stdout, (ppList*)&my_list);
    return 0;
}
```

Компиляция(требует установленного компилятора [ppclang](https://gitverse.ru/kpdev/llvm-project/content/pp-extension-v2)):

```bash
ppclang my_program.c -I/usr/local/include -L/usr/local/lib -lppc_standard_containers -o my_program
```


### Подробнее о процедурно-параметрической парадигме

[http://www.softcraft.ru/ppp/](http://www.softcraft.ru/ppp/)
