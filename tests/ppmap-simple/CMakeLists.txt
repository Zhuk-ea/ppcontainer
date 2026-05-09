# set minimum cmake version
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
SET(CMAKE_C_COMPILER ppclang)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

# Установка переменной со списком исходников
set(SOURCE_FILES
    # headers

    #sources
    test-ppmap-simple.c
)

# Для того, чтобы clang понимал файлы с другим расширением (ppc, например)
# set_source_files_properties(
#     ${SOURCE_FILES}
#     PROPERTIES
#     LANGUAGE C
# )

add_executable(test-ppmap-simple ${SOURCE_FILES})
add_test(NAME ppmap-simple COMMAND test-ppmap-simple)

# Линковка программы с библиотекой body
target_link_libraries(test-ppmap-simple
  -Wl,--whole-archive
  ppmap
  -Wl,--no-whole-archive
)
