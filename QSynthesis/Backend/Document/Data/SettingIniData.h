#ifndef SETTINGINIDATA_H
#define SETTINGINIDATA_H

#include "Utils/FileNameSet.h"

class SettingIniData {
    Q_SINGLETON(SettingIniData)

public:
    SettingIniData();
    virtual ~SettingIniData();

    void clear();

    QString tool1Path;
    QString tool2Path;

    FileNameSet projects;
    FileNameSet folders;
    FileNameSet wavtools;
    FileNameSet resamplers;

    QRect windowRect;
    bool windowMaximized;

    bool tracksFormVisibility;
    bool editorFormVisibility;
    bool paramsFormVisibility;

    int lastQuantize;
    bool ignoreRestsWhenInsert;
    bool replaceLyricsWhenInsert;
    bool separateCharWhenInsert;

    int themeIndex;
};

#endif // SETTINGINIDATA_H
