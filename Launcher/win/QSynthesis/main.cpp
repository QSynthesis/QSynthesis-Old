#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#define _AFXDLL
#define _UNICODE
#define _WIN32_WINNT 0x0502

#include <afxwin.h>

int main() {
    // Get Command Line
    LPWSTR *szArgList;
    int argCount;
    szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);

    if (!szArgList) {
        MessageBox(NULL, L"Unable to parse command line.", L"Error", MB_ICONERROR);
        return -1;
    }

    // Get Launcher Executable Path
    TCHAR buff[MAX_PATH];
    ::GetModuleFileName(NULL, buff, MAX_PATH);

    CString strExePath = buff;
    strExePath = strExePath.Left(strExePath.ReverseFind('\\'));

    CString strAppPath = strExePath + _T("\\app\\QSynthesis.exe");

    // Arrange Command Line
    CString strCmdLine = strAppPath;
    for (int i = 1; i < argCount; i++) {
        CString curParam = szArgList[i];
        bool hasSpace = curParam.Find(_T(" ")) >= 0;

        if (hasSpace) {
            curParam = _T("\"") + curParam + _T("\"");
        }

        strCmdLine += _T(" ");
        strCmdLine += curParam;
    }

    // Prepare process
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    // Start the child process.
    if (!CreateProcess(NULL, // No module name (use command line).
                       strCmdLine.GetBuffer(),    // Command line.
                       NULL,             // Process handle not inheritable.
                       NULL,             // Thread handle not inheritable.
                       FALSE,            // Set handle inheritance to FALSE.
                       0,                // No creation flags.
                       NULL,             // Use parent's environment block.
                       strExePath,       // Use parent's starting directory.
                       &si,              // Pointer to STARTUPINFO structure.
                       &pi)              // Pointer to PROCESS_INFORMATION structure.
            ) {
        ::MessageBox(NULL, TEXT("QSynthesis application not found, please check directory!"), TEXT("Error"),
                     MB_ICONERROR);
    }

    // Wait until child process exits.
    // WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}