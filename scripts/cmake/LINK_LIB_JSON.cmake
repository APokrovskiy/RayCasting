# Подключение библиотеки JSON
macro(LINK_LIB_JSON output)
    message( 
"
++++++++++++++++++++++++++++++++++++++++++++++
         __________________________
        | Загрузка библиотеки json |
        |         Подождите        |
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
++++++++++++++++++++++++++++++++++++++++++++++

") 
    # Указания Сведений о библиотеке json
    FetchContent_Declare(
        ${output}
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
    )
    
    # Активация библиотеки
    FetchContent_MakeAvailable(${output})
endmacro()
