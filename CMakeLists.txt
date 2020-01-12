cmake_minimum_required(VERSION 3.15)
project(MSU_4_1_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(MSU_4_1_2 main.c odu.c odu.h init_functions.c plot.c)
target_link_libraries(MSU_4_1_2 m)