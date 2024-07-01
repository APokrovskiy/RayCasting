# TODO: Заккоментировать
add_library(libobjects Button.cpp Camera.cpp World.cpp world_map/Map.cpp world_map/MiniMap.cpp) # Добавляем ваши cpp-файлы в библиотеку libObjects
target_include_directories(libobjects 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(libobjects ${libsfml} libkernel)