###############################################
# Ваш компилятор должен поддерживать C++17
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
###############################################

project( Ray-Casting LANGUAGES CXX )

# Статическая линковка библиотек
set(BUILD_SHARED_LIBS OFF)

# SFML
###################################################
include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)
###################################################

# Помещаем исходники в переменную SOURCES
#########################################
include_directories(inc)
file(GLOB_RECURSE SOURCES
    "source/*.cpp"
    "inc/*.hpp"
)
#########################################

# Создание исполняемого файла
##############################################
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-graphics
    sfml-window 
    sfml-system
)
##############################################

# Убираем консоль
#################################
include(cmake/GUI_PROGRAM.cmake)
GUI_PROGRAM(${PROJECT_NAME})
#################################

# Копируем папку ресурсов
###############################################################
include(cmake/CP.cmake)
CP(${CMAKE_CURRENT_SOURCE_DIR}/fonts ${CMAKE_BINARY_DIR}/fonts)
###############################################################