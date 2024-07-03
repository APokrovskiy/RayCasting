# Сборка проекта
# Для того чтобы собрать проект, нужно установить установить утилиты gcc, cmake и ninja, а также добавить их в переменные среды PATH:
# Теперь перейдите в директорию с файлом CMakeLists.txt в cmd (Не в powershell) и введите команду:
# запустите скрипт scripts/build.cmd(для Windows) или scripts/build.sh (Для Линукс) Из проводника (или из директории, где он находится) #TODO: Проверить на линукс
# смотрите результат в папке build Ray-Casting.exe

message("

        -------------------------------------
        Начинается сборка проекта Ray-Casting
        -------------------------------------

")

# Минимальная допустимая версия системы сборки Cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Название проекта
project(Ray-Casting
        LANGUAGES CXX
        VERSION 1.2.0
        DESCRIPTION "3D Лабиринт: Визуализация работы алгоритма ray-casting"
)

# Импорт модулей
include(FetchContent)
include(scripts/cmake/LINK_LIB_SFML.cmake)
include(scripts/cmake/LINK_LIB_JSON.cmake)
include(scripts/cmake/GUI_PROGRAM.cmake)
include(scripts/cmake/LINK_PYTHON_REQUIREMENTS.cmake)
include(scripts/cmake/CP.cmake)

# Тишина от FetchContent
set(FETCHCONTENT_QUIET True)

# Отключение динамической компоновки библиотеки
set(BUILD_SHARED_LIBS OFF)

# подключение SFML и json
LINK_LIB_SFML(sfml 2.5.1)
LINK_LIB_JSON(json)
set(libsfml sfml-graphics sfml-window sfml-system sfml-audio)


add_subdirectory(source)

# Без консоли
GUI_PROGRAM(${PROJECT_NAME})

# Установка python зависимостей
LINK_PYTHON_REQUIREMENTS(${CMAKE_SOURCE_DIR}/Configurator/requirements.txt)

# Копирование директории с конфигуратором в папку с исполняемым файлом
message(
        "
++++++++++++++++++++++++++++++++++++++++++++++
________________________________
|    Копирование Configurator   |
|           Подождите           |
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
++++++++++++++++++++++++++++++++++++++++++++++
")
CP(${CMAKE_CURRENT_SOURCE_DIR}/Configurator ${CMAKE_BINARY_DIR}/Configurator)

# Добавление целей из папки headers в HEADERS
message(
        "
++++++++++++++++++++++++++++++++++++++++++++++
         __________________________
        |    Компиляция проекта    |
        |         Подождите        |
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
++++++++++++++++++++++++++++++++++++++++++++++
")