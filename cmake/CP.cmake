# Макрос для копирования директорий
macro(CP src dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${src} ${dst}
        RESULT_VARIABLE ret
        OUTPUT_VARIABLE out 
        ERROR_VARIABLE err )
    if(ret)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${err}")
    endif()
endmacro()
