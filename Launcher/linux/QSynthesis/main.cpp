#include <iostream>
#include <cstring>
#include <fstream>

#include <unistd.h>
#include <linux/limits.h>

using namespace std;

const char strVersion[] = "0.1.77";

int main(int argc, char **argv, char **envp) {
    // Get Executable Full Path
    char dir[PATH_MAX];
    memset(dir, 0, PATH_MAX);
    int n = readlink("/proc/self/exe", dir, PATH_MAX);

    // Get Application Full Path
    string strExePath(dir);
    string strDirPath = strExePath.substr(0, strExePath.find_last_of('/'));
    string strAppPath = strDirPath + "/app/QSynthesis";

    // Check Argument
    if (argc == 2 && !strcmp(argv[1], "-d")) {
        string filename = strDirPath + "/QSynthesis.desktop";

        // Write .desktop File
        fstream fs;
        fs.open(filename, ios::out);
        if (fs.fail()) {
            cout << "Failed to create desktop shortcut." << endl;
            return -1;
        }

        fs << "[Desktop Entry]" << endl;
        fs << "Categories=Utility;Audio;" << endl;
        fs << "Encoding=UTF-8" << endl;
        fs << "Version=" << strVersion << endl;
        fs << "Type=Application" << endl;
        fs << "Terminal=false" << endl;
        fs << "Exec=\"" << strExePath << "\" %F" << endl;
        fs << "Name=QSynthesis" << endl;
        fs << "Icon=" << strDirPath << "/app/logo" << endl;
        fs << "Comment=\"Cross-platform vocal synthesis frontend\"" << endl;

        fs.close();

        // Give Execute Permission
        string cmd = "chmod +x \"" + filename + "\"";
        system(cmd.c_str());

        cout << "Successfully create desktop shortcut." << endl;

        return 0;
    } else if (argc == 2 && !strcmp(argv[1], "-h")) {
        cout << "Usage: QSynthesis -d" << endl;
        cout << "   Or: QSynthesis <filename>" << endl;
        cout << "   Or: QSynthesis <dirname>" << endl;
        cout << endl;

        cout << "Option specification:" << endl;
        cout << "       -d Create desktop shortcut automatically." << endl;
        cout << "       (Paths in desktop file is based on current directory)" << endl;
        cout << "       -h Print this message." << endl;

        return 0;
    }

    char **newArgv = new char *[argc];
    newArgv[0] = new char[strAppPath.size() + 1];
    strcpy(newArgv[0], strAppPath.c_str());
    for (int i = 1; i < argc; ++i) {
        newArgv[i] = argv[i];
    }

    // Create Child Process
    if (fork() == 0) {
        // Set Working Directory
        const char *currentDir = strDirPath.c_str();
        chdir(currentDir);
        setenv("PWD", currentDir, 1);

        execve(strAppPath.c_str(), newArgv, envp);

        // If error occurs, the following codes will be loaded
        cout << "Failed to execute application." << endl;
    }

    // Parent Process Exit Normally
    return 0;
}
