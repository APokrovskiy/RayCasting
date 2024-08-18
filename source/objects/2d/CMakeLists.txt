add_subdirectory(any_functional)
add_subdirectory(phisic)

add_library(2d INTERFACE)

target_link_libraries(2d INTERFACE
    any_functional
    phisic
    ${libsfml}
)