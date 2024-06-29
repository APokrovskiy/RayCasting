set(SOURCES PARENT_SCOPE)


add_subdirectory(start_configurator)
add_subdirectory(Objects)
add_subdirectory(Settings_Updater)

set(libUserLibs libConfigurator libObjects libSettingsUpdater)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp )


target_include_directories(${PROJECT_NAME} PUBLIC ${sfml_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${libUserLibs}
    ${libsfml}
    nlohmann_json::nlohmann_json
)


add_library(librc ray-cast.hpp ray-cast.cpp)
target_include_directories(librc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

