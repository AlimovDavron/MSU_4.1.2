cmake_minimum_required(VERSION 3.15)
project(MSU_4_1_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(MSU_4_1_2 main_01_36.c odu_01_36.c odu_01_36.h init_functions.c plot_01_36.c)
target_link_libraries(MSU_4_1_2 m)