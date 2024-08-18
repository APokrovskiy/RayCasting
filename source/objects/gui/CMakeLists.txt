add_library(gui Map.cpp MiniMap.cpp FPSLabel.cpp Button.cpp)
target_include_directories(gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) # Указываем путь к заголовочным файлам

target_link_libraries(gui ${libsfml})