cmake_minimum_required(VERSION 3.15)
project(Domination)

set(CMAKE_C_STANDARD 99)

add_executable(Domination main.c Object_Definition.h Game_Init.h Game_Init.c ASCII_IO.h ASCII_IO.c Game_Logic.h Game_Logic.c Unit_Tests.c Unit_Tests.h)