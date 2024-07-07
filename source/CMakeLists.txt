set(SOURCES PARENT_SCOPE)

add_subdirectory(kernel)
add_subdirectory(objects)
add_subdirectory(settings_manager)
add_subdirectory(start_configurator)

# Чтобы exe-шник появлялся в нужном месте для открытия конфигуратора
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp)

# Подключение хедеров SFML
target_include_directories(${PROJECT_NAME} PUBLIC ${sfml_SOURCE_DIR}/include) 


target_link_libraries(${PROJECT_NAME} PUBLIC
    objects
    settings_manager
    start_configurator
    kernel
    ${libsfml}
)
