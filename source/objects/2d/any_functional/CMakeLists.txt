add_library(any_functional Camera.cpp World.cpp)
target_include_directories(any_functional
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(any_functional ${libsfml})