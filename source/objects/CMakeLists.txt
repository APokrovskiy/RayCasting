add_subdirectory(2d)
#add_subdirectory(3d)
add_subdirectory(gui)
add_subdirectory(other)

add_library(objects INTERFACE)

target_link_libraries(objects INTERFACE
    2d
#    3d
    gui
    other
    ${libsfml}
)