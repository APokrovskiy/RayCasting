# Сборка проекта
#############################################################################################################################################
# Для того чтобы собрать проект, нужно установить установить утилиты gcc, cmake и ninja, а также добавить их в переменные среды PATH:       #
# Теперь перейдите в директорию с файлом CMakeLists.txt в cmd (Не в powershell) и введите команду:                                          #
# cmake -DCMAKE_CXX_COMPILER=c++ -DCMAKE_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -G Ninja -S . -B build && cmake --build build #
# смотрите результат в папке build Ray-Casting.exe                                                                                          #
#############################################################################################################################################

# Минимальная допустимая версия системы сборки Cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Стандарт C++ 
set(CMAKE_CXX_STANDARD 11)

# Название проекта
project(Ray-Casting LANGUAGES CXX)

# Импорт модуля для автоматического скачивания библиотеки с интернетв
include(FetchContent)

# Версия графической библиотеки SFML
set(SFML_VERSION "2.5.1")

# Указания Сведений о библиотеке
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)
# Отключение динамической компоновки библиотеки
set(BUILD_SHARED_LIBS OFF)

# Настройки SFML
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)

# Активация SFML
FetchContent_MakeAvailable(sfml)

# Подключение Хедеров
include_directories("./headers")

set(SOURCES 
    "source/main.cpp"
    "source/ray-cast.cpp"
    "source/Camera.cpp"
)

set(HEADERS
    "headers/ray-cast.hpp"
    "headers/Camera.hpp"
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
)

# Линковка Библиотеки с Исполняемым файлом
target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


# Программа GUI (Без консоли)
if(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
elseif(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE true)
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    )
endif()