# Подключение библиотеки SFML
macro(LINK_LIB_SFML output SFML_VERSION)

    message( 
"
++++++++++++++++++++++++++++++++++++++++++++++
        __________________________
        | Загрузка библиотеки sfml |
        |         Подождите        |
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
++++++++++++++++++++++++++++++++++++++++++++++

") 

    # Указания Сведений о библиотеке SFML
    FetchContent_Declare(
        ${output}
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        ${SFML_VERSION}
    )

    # Настройки SFML
    set(SFML_BUILD_EXAMPLES OFF)
    set(SFML_BUILD_DOC OFF)
    set(SFML_BUILD_NETWORK ON)
    set(SFML_BUILD_AUDIO ON)
    set(SFML_BUILD_GRAPHICS ON)
    set(SFML_BUILD_WINDOW ON)

    # Активация библиотеки
    FetchContent_MakeAvailable(${output})

endmacro()

