#include "system_without_console.hpp"

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/wait.h>
#endif

static std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}


void system_without_console_output(const std::wstring& cmd)
{
#ifdef _WIN32
    STARTUPINFOW si = { sizeof(si) }; // Use STARTUPINFOW for Unicode support
    PROCESS_INFORMATION pi;

    std::wstring fullCommand = cmd + L" > nul 2>&1"; // Create full command including redirection

    LPWSTR writableCmd = const_cast<LPWSTR>(fullCommand.c_str()); // Get non-const pointer to the C-style string

    if (CreateProcessW(NULL, writableCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

#elif defined(__linux__) || defined(__APPLE__)
    pid_t childPid = fork();
    if (childPid == 0)
    {
        // Это код потомка
        std::string narrowCmd = wstring_to_string(cmd);
        execl("/bin/sh", "sh", "-c", narrowCmd.c_str(), (char *)0);
        exit(0); // Выходим, чтобы избежать выполнения кода родительским процессом
    }
    else
    {
        // Это код родительского процесса
        int status;
        waitpid(childPid, &status, 0); // Ждем завершение потомка
    }

#endif
}
