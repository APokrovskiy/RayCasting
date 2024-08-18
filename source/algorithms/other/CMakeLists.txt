add_subdirectory(open_other_files)

add_library(other_a INTERFACE)

target_link_libraries(other_a INTERFACE
    open_other_files
    ${libsfml}
)