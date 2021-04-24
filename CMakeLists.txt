cmake_minimum_required(VERSION 3.12)
project(chapter1 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(chapter1 main.c include/error.c)