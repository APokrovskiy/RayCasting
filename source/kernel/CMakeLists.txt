# TODO: Заккоментировать
add_library(libkernel ray-cast.cpp Collider.cpp) 
target_include_directories(libkernel 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(libkernel ${libsfml})