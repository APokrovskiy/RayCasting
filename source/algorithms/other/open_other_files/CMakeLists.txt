add_library(open_other_files start_configurator.cpp system_without_console.cpp)

target_include_directories(open_other_files
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(open_other_files ${libsfml})