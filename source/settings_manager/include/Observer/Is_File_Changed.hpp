#pragma once
#include <filesystem>
#include <string>

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