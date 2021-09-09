#ifndef SETTINGINIDATA_H
#define SETTINGINIDATA_H

#include "Utils/FileNameSet.h"

class SettingIniData {
public:
    SettingIniData();

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
};

#endif // SETTINGINIDATA_H
