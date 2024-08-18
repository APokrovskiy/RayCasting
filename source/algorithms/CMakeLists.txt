add_subdirectory(2d)
#add_subdirectory(3d)
add_subdirectory(other)

add_library(algorithms INTERFACE)

target_link_libraries(algorithms INTERFACE
    2d_a
#    3d
    other_a
    ${libsfml}
)