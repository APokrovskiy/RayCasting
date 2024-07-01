# Подгрузка всех python зависимостей из requirements.txt
macro(LINK_PYTHON_REQUIREMENTS requirements_path)

    message(
"
++++++++++++++++++++++++++++++++++++++++++++++
    ________________________________
    | Подключаем Python зависимости |
    |           Подождите           |
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
++++++++++++++++++++++++++++++++++++++++++++++
")
        
    
    execute_process(COMMAND python -m pip install -q -r ${requirements_path}
    RESULT_VARIABLE pip_result
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

    if(NOT ${pip_result} EQUAL 0)
    message(FATAL_ERROR "Failed to install Python requirements. Try installing python and pip!")
    endif()

endmacro()