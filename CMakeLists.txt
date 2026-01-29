# set minimum cmake version
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# project name and language
project(containers)
SET(CMAKE_C_COMPILER ppclang)
set(CMAKE_C_STANDARD 17)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}/../lib")

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type is Debug" FORCE)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(BEFORE
    src/include
)
link_directories(./lib)

add_subdirectory(src/ppvector)
add_subdirectory(src/pplist)

# add_subdirectory(tests/ppvector-common)
add_subdirectory(tests/pplist-common)
add_subdirectory(tests/pplist-mytests)
add_subdirectory(tests/pplist-swap-move-copy)
add_subdirectory(tests/pplist-iterator)
add_subdirectory(tests/pplist-erase)
add_subdirectory(tests/pplist-remove)
add_subdirectory(tests/pplist-remove-if)
add_subdirectory(tests/pplist-dev-tests)