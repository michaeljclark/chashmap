cmake_minimum_required(VERSION 3.12)

project(chashmsp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)
add_executable(test_hmap tests/test_hmap.c)
add_executable(bench_hmap tests/bench_hmap.c)
