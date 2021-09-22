#ifndef SHORTCUTSFILE_H
#define SHORTCUTSFILE_H

#include "Data/ShortcutsData.h"
#include "FileManager.h"
#include "QUtils.h"

#include <QFile>
#include <QFileSystemWatcher>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

class ShortcutsFile : public FileManager {
    Q_OBJECT
public:
    explicit ShortcutsFile(QObject *parent = nullptr);
    explicit ShortcutsFile(const QString &filename, QObject *parent = nullptr);
    ~ShortcutsFile();

    void setData(const ShortcutsData &data);
    ShortcutsData data() const;

private:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

private:
    ShortcutsData m_data;

private:
    static QJsonObject toJson(const ShortcutsData &keys);
    static ShortcutsData fromJson(const QJsonObject &obj);
};

#endif // SHORTCUTSFILE_H
