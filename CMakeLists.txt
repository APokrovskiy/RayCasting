# cmake -Wno-dev -DCMAKE_CXX_COMPILER=c++ -DCMAKE_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -G Ninja -S . -B build && cmake --build build

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


project(Ray-Casting
        LANGUAGES CXX # + Python
        VERSION 1.4.0
        DESCRIPTION "3D Лабиринт: Визуализация работы алгоритма ray-casting"
)

find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)

set(libsfml sfml-graphics sfml-window sfml-system)

add_subdirectory(source)

include(scripts/cmake/GUI_PROGRAM.cmake)
GUI_PROGRAM(${PROJECT_NAME})

message(STATUS " Копирование Configurator ")
include(scripts/cmake/CP.cmake)
CP(${CMAKE_CURRENT_SOURCE_DIR}/Configurator ${CMAKE_BINARY_DIR}/Configurator)

message(STATUS " Компиляция проекта ")