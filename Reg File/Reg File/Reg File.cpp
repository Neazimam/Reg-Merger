#include <windows.h>
#include <iostream>

int main() {
    // Get the path of the current executable
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // Remove the executable name to get the directory path
    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        path = path.substr(0, pos);
    }

    // Append the .reg file name
    std::string regFilePath = path + "\\Epic.reg"; // 注册本机.reg = "注册本机.reg"

    // Prepare the command
    std::string command = "regedit.exe /s \"" + regFilePath + "\"";

    // Start the process hidden
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    if (CreateProcessA(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Successfully started the process
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        MessageBoxA(NULL, "Failed to merge registry.", "Error", MB_OK | MB_ICONERROR);
    }

    return 0;
}
