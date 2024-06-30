add_library(libsettings_manager Settings_Updater.cpp Observer/Is_File_Changed.cpp settings.cpp)

target_include_directories(libsettings_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # TODO: Разделить инклюды на PRIVATE и PUBLIC

target_link_libraries(libsettings_manager PUBLIC nlohmann_json::nlohmann_json libobjects)
