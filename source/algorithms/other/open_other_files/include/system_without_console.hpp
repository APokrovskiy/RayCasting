#pragma once

#include <string>

// Кроссплатформенное решение для исполнения консольных команд без появления окна консоли
void system_without_console_output(const std::wstring &cmd);