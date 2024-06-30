# Сборка проекта
#############################################################################################################################################
# Для того чтобы собрать проект, нужно установить установить утилиты gcc, cmake и ninja, а также добавить их в переменные среды PATH:       #
# Теперь перейдите в директорию с файлом CMakeLists.txt в cmd (Не в powershell) и введите команду:                                          #
# cmake -DCMAKE_CXX_COMPILER=c++ -DCMAKE_CXX_FLAGS="-static -static-libgcc -static-libstdc++" -G Ninja -S . -B build && cmake --build build #
# смотрите результат в папке build Ray-Casting.exe                                                                                          #
#############################################################################################################################################

# TODO: Сделать Сообщения об ошибках

# Минимальная допустимая версия системы сборки Cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Стандарт C++ 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Название проекта
project(Ray-Casting 
    LANGUAGES CXX
    VERSION 1.1.0
    DESCRIPTION "Программа иллюстрирует работу алгоритма рендеринга Ray-Casting"
)

# Импорт модуля для автоматического скачивания библиотеки с интернета
include(FetchContent)

# Версия графической библиотеки SFML
set(SFML_VERSION 2.5.1)


# Указания Сведений о библиотеке SFML
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        ${SFML_VERSION}
)

# Указания Сведений о библиотеке json
FetchContent_Declare(
    json
    GIT_REPOSITORY "https://github.com/nlohmann/json.git"
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

# Активация SFML и json
FetchContent_MakeAvailable(sfml json)
set(libsfml sfml-graphics sfml-window sfml-system sfml-audio)

# Добавление целей из папки headers в HEADERS
add_subdirectory(source)

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

# Макрос для копирования директорий
macro(copy_directory src dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${src} ${dst}
        RESULT_VARIABLE ret
        OUTPUT_VARIABLE out 
        ERROR_VARIABLE err )
    if(ret)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${err}")
    endif()
endmacro()

# Configurator
###############################################################################################################
# Подгрузка всех python зависимостей
execute_process(COMMAND python -m pip install -r ${CMAKE_SOURCE_DIR}/RayCastingConfigurator/requirements.txt
                RESULT_VARIABLE pip_result
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if(NOT ${pip_result} EQUAL 0)
    message(FATAL_ERROR "Failed to install Python requirements. Try installing python and pip!")
endif()

#Копирование директории с конфигуратором в папку с исполняемым файлом
copy_directory(${CMAKE_CURRENT_SOURCE_DIR}/RayCastingConfigurator   ${CMAKE_BINARY_DIR}/RayCastingConfigurator)
################################################################################################################
