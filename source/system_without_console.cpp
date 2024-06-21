
#include "system_without_console.hpp"

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <sys/wait.h>
#endif


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

#elif defined(__linux__) || defined(__APPLE__) // TODO: Проверить совместимость с линукс
    if (fork() == 0) {
        execl("/bin/sh", "sh", "-c", (std::string{"nohup "} + cmd + " > /dev/null 2>&1 &").c_str(), (char*)0);
    } else {
        wait(NULL);
    }
#endif
}
