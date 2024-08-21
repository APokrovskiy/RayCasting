cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(Ray-Casting
        LANGUAGES CXX 
        VERSION 1.4.0
        DESCRIPTION "3D Лабиринт: Визуализация работы алгоритма ray-casting"
)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

set(libsfml sfml-graphics sfml-window sfml-system)

include_directories(source)
add_subdirectory(source)

include(cmake/GUI_PROGRAM.cmake)
GUI_PROGRAM(${PROJECT_NAME})

include(cmake/CP.cmake)
CP(${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_BINARY_DIR}/fonts)