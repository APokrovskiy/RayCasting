#pragma once

#include <fstream>
#include <thread>
#include <chrono>
#include "../json.hpp"

#include "Observer/Is_File_Changed.hpp"

// Дескриптор json файла, следящий за его изменением
template <class Deserialization_Struct>
class JSON_File_Observer
{
public:
    JSON_File_Observer(const std::string &path_to_json_file_settings)
        : is_file_changed{path_to_json_file_settings}
    {
        path_to_file = path_to_json_file_settings;
    }

    Deserialization_Struct update_settings(std::function<Deserialization_Struct(const nlohmann::json &)> load_settings)
    {
        std::this_thread::sleep_for(std::chrono::microseconds{100}); // Задержка программы для корректной подгрузки файла
        std::ifstream file_setts_json{path_to_file};
        nlohmann::json data;
        if (!file_setts_json)
            throw std::runtime_error("File settings can not open\n");
        else
            data = nlohmann::json::parse(file_setts_json);

        return load_settings(data);
    }

    Is_File_Changed is_file_changed;

private:
    std::string path_to_file;
};
