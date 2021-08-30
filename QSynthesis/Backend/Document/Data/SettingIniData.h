#ifndef SETTINGINIDATA_H
#define SETTINGINIDATA_H

#include "Utils/FileNameSet.h"

class SettingIniData {
public:
    SettingIniData();

    void clear();

    bool cacheEnable;
    bool cacheDeleteBySize;
    int cacheDeleteSize;

    bool noOtoReport;
    bool noCopyGenon;

    bool noBatchMode;
    int threadNumber;

    QString tool1Path;
    QString tool2Path;

    FileNameSet projects;
    FileNameSet folders;
    FileNameSet wavtools;
    FileNameSet resamplers;

    QRect windowRect;
    bool windowMaximized;
};

#endif // SETTINGINIDATA_H
