add_library(2d_a ray-cast.cpp)
target_include_directories(2d_a
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(2d_a ${libsfml})