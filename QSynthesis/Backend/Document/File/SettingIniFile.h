#ifndef SETTINGINIFILE_H
#define SETTINGINIFILE_H

#include "FileManager.h"
#include "QSFileData.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QRect>
#include <QTextCodec>
#include <QTextStream>

class SettingIniFile : public FileManager {
    Q_OBJECT
public:
    explicit SettingIniFile(QObject *parent = nullptr);
    explicit SettingIniFile(const QString &filename, QObject *parent = nullptr);
    ~SettingIniFile();

private:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

public:
    SettingIniData data() const;
    void setData(const SettingIniData &data);

private:
    SettingIniData m_data;
};

#endif // SETTINGINIFILE_H
