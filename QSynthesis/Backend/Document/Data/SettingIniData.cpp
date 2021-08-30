#include "SettingIniData.h"

SettingIniData::SettingIniData() {
    projects.setType(FileNameSet::File);
    folders.setType(FileNameSet::Directory);
    wavtools.setType(FileNameSet::File);
    resamplers.setType(FileNameSet::File);

    clear();
}

void SettingIniData::clear() {
    cacheEnable = true;
    cacheDeleteBySize = false;
    cacheDeleteSize = 0;

    noOtoReport = false;
    noCopyGenon = true;

    noBatchMode = false;
    threadNumber = 1;

    tool1Path = "";
    tool2Path = "";

    projects.clear();
    folders.clear();
    wavtools.clear();
    resamplers.clear();

    windowRect = NO_RECT;
    windowMaximized = false;
}
