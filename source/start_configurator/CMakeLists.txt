add_library(libConfigurator start_configurator.cpp system_without_console.cpp)

target_include_directories(libConfigurator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )