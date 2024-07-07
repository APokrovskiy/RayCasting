# TODO: Заккоментировать

add_library(objects
    Button.cpp 
    Camera.cpp 
    World.cpp 
    world_map/Map.cpp
    world_map/MiniMap.cpp
) 
target_include_directories(objects 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  ${sfml_SOURCE_DIR}/include

) # Указываем путь к заголовочным файлам

target_link_libraries(objects ${libsfml} kernel)