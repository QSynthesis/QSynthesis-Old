#include <iostream>
#include <cstring>

#include <unistd.h>
#include <linux/limits.h>

using namespace std;

int main(int argc, char **argv, char **envp) {
    // Get Executable Full Path
    char dir[PATH_MAX];
    memset(dir, 0, PATH_MAX);
    int n = readlink("/proc/self/exe", dir, PATH_MAX);

    // Get Application Full Path
    string strExePath(dir);
    string strDirPath = strExePath.substr(0, strExePath.find_last_of('/'));
    string strAppPath = strDirPath + "/app/QSynthesis";

    char **newArgv = new char *[argc];
    newArgv[0] = new char[strAppPath.size() + 1];
    strcpy(newArgv[0], strAppPath.c_str());
    for (int i = 1; i < argc; ++i) {
        newArgv[i] = argv[i];
    }

    // Set Working Directory
    setenv("PWD", strDirPath.c_str(), 1);

    // Create Child Process
    if (fork() == 0) {
        execve(strAppPath.c_str(), newArgv, envp);
    }

    // Parent Process Exit Normally
    return 0;
}
