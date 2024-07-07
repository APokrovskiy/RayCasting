add_library(start_configurator 
    start_configurator.cpp
    system_without_console.cpp
)

target_include_directories(start_configurator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)