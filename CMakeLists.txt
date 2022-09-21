cmake_minimum_required(VERSION 3.16)

project(labyrinth LANGUAGES CXX)

#Enable debugging flags
option(DEBUGGING "Debugging options" ON)
if(DEBUGGING)
    add_compile_options(-std=c++11 -Wall -g)
else()
    add_compile_options(-std=c++11 -O2)
endif(DEBUGGING)

set(APP_NAME labyrinth)
set(APP_LIB_NAME labyrinth_lib)

#Directory with source code
add_subdirectory(src)

#Compilaton of the unit tests
option(COMPILE_UTESTS "Compile the unit tests" ON)
if(COMPILE_UTESTS)
    add_subdirectory(utests)
endif(COMPILE_UTESTS)
