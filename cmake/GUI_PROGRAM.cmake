# Программа GUI (Без консоли)
macro(GUI_PROGRAM target)
    if(WIN32)
        set_target_properties(${target} PROPERTIES WIN32_EXECUTABLE true)
    elseif(APPLE)
        set_target_properties(${target} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${target}
        )
    endif()
endmacro()
