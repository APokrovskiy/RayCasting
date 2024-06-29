# TODO: Заккоментировать
add_library(libObjects Button.cpp Camera.cpp World.cpp) # Добавляем ваши cpp-файлы в библиотеку libObjects
target_include_directories(libObjects 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include  ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(libObjects ${libsfml} librc)