#include "Observer/Is_File_Changed.hpp"

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
