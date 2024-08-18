add_library(phisic Collider.cpp)
target_include_directories(phisic
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(phisic ${libsfml})
