cmake_minimum_required(VERSION 3.16)

project(labyrinth LANGUAGES CXX)

option(DEBUGGING "Debugging" ON)
option(WITH_QT_UI "With Qt user interface" OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

if(WITH_QT_UI)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    find_package(Qt5Widgets REQUIRED)
    qt5_use_modules(labyrinth Widgets)
endif()

if(DEBUGGING)
    set(CMAKE_CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()
add_executable(labyrinth commands.cpp
                         door.cpp
                         labyrinth.h
                         main.cpp)

target_include_directories(labyrinth PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
