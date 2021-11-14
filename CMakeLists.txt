cmake_minimum_required(VERSION 3.1)

project(kmeans)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE "Debug")

include_directories(${PROJECT_SOURCE_DIR}/kmeans)
include_directories(${PROJECT_SOURCE_DIR}/geometric)
include_directories(${PROJECT_SOURCE_DIR}/topology)
# message(STATUS  ${SRC})

add_compile_options(-Wall -Werror -O2 -g)

add_subdirectory(test)