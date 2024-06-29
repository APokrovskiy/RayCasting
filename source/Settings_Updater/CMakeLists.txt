add_library(libSettingsUpdater Settings_Updater.cpp Observer/Is_File_Changed.cpp settings.cpp)

target_include_directories(libSettingsUpdater PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # TODO: Разделить инклюды на PRIVATE и PUBLIC

target_link_libraries(libSettingsUpdater PUBLIC nlohmann_json::nlohmann_json libObjects)
