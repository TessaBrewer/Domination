cmake_minimum_required(VERSION 3.15)
project(Domination)

set(CMAKE_C_STANDARD 99)

add_definitions(-DUNIT_TEST)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
SET(GCC_COVERAGE_LINK_FLAGS "-lcunit")
add_definitions(-DTEST)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(Domination main.c Object_Definition.h Game_Init.h Game_Init.c ASCII_IO.h ASCII_IO.c Game_Logic.h Game_Logic.c Unit_Tests.c Unit_Tests.h)