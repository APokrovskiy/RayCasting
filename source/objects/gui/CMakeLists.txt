add_library(gui Map.cpp MiniMap.cpp FPSLabel.cpp)
target_include_directories(gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${sfml_SOURCE_DIR}/include
) 

target_link_libraries(gui ${libsfml})