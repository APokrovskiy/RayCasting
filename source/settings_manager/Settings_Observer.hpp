#pragma once

#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include "nlochmann_json.hpp"


class Is_File_Changed
{
public:
    Is_File_Changed(const std::string &path_to_file);

    bool operator()() &;           // Только lvalue-ссылки
    bool operator()() && = delete; // Недоступен для rvalue-ссылок

private:
    std::filesystem::path path;
    std::filesystem::file_time_type last_write_time;
};

// Дескриптор json файла, следящий за его изменением
template <class Deserialization_Struct>
class Settings_Observer
{
public:
    Settings_Observer(const std::string &path_to_json_file_settings)
        : is_file_changed{path_to_json_file_settings}, path_to_file{path_to_json_file_settings} {}

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


Is_File_Changed::Is_File_Changed(const std::string &path_to_file)
    : path{path_to_file}
{
    last_write_time = std::filesystem::last_write_time(path);
}

bool Is_File_Changed::operator()() & // Только lvalue-ссылки
{
    if (last_write_time != std::filesystem::last_write_time(path))
    {
        last_write_time = std::filesystem::last_write_time(path);
        return true;
    }
    return false;
}