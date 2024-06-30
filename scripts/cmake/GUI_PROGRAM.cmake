# Программа GUI (Без консоли)
macro(GUI_PROGRAM target)
    if(UNIX AND NOT APPLE)
    set_target_properties(${target} PROPERTIES LINK_FLAGS "-mwindows")
    elseif(WIN32)
    set_target_properties(${target} PROPERTIES WIN32_EXECUTABLE true)
    elseif(APPLE)
    set_target_properties(${target} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME ${target}
    )
    endif()
endmacro()
