add_library(settings_manager 
    Settings_Updater.cpp 
    Observer/Is_File_Changed.cpp 
    settings.cpp
)

target_include_directories(settings_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # TODO: Разделить инклюды на PRIVATE и PUBLIC

target_link_libraries(settings_manager PUBLIC objects)
