cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

set(SOURCE_LIB
    ppmap.c
    ppgeneral.c
)

add_library(ppmap STATIC ${SOURCE_LIB})
target_include_directories(ppmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)