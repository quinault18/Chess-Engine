cmake_minimum_required(VERSION 3.15)

project(Chess VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

