#ifndef SETTINGINIFILE_H
#define SETTINGINIFILE_H

#include "BaseFile.h"
#include "Macros.h"
#include "QFileSet.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QRect>
#include <QTextCodec>
#include <QTextStream>

class SettingIniFile : public BaseFile {
    Q_CHARSET
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

    QFileSet projects;
    QFileSet folders;
    QFileSet wavtools;
    QFileSet resamplers;

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
