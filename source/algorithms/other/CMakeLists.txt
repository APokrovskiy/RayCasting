add_library(other_a INTERFACE)

target_link_libraries(other_a INTERFACE
    ${libsfml}
)