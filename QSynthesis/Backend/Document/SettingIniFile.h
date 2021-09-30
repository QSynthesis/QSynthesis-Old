#ifndef SETTINGINIFILE_H
#define SETTINGINIFILE_H

#include "Files/BaseFile.h"
#include "Files/QSettingFile.h"
#include "Macros.h"
#include "Utils/FileNameSet.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QRect>
#include <QTextCodec>
#include <QTextStream>

#define qSetting SettingIniFile::instance()

class SettingIniFile : public BaseFile {
    Q_CHARSET
    Q_SINGLETON(SettingIniFile)
public:
    SettingIniFile();
    SettingIniFile(const QString &filename);
    ~SettingIniFile();

private:
    void init();

    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

public:
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

    bool noteVisibility;
    bool pitchVisibility;
    bool envelopeVisibility;
    bool paramsVisibility;

    bool playHeadCenter;

    bool spriteVisibility;
    double spriteOpacity;
    Qt::Corner spritePosition;

    int themeIndex;
};

#endif // SETTINGINIFILE_H
