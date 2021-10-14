#ifndef SHORTCUTSFILE_H
#define SHORTCUTSFILE_H

#include "BaseFile.h"
#include "QUtils.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

class ShortcutsFile : public BaseFile {
public:
    ShortcutsFile();
    ShortcutsFile(const QString &filename);
    ~ShortcutsFile();

    void setData(const ShortcutsFile &another);
    void makeDefault();

protected:
    ShortcutsFile(Qs::VariableSource source);

    friend class Application;

private:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

public:
    QList<QKeySequence> commonShortcuts;
    QList<QKeySequence> projectShortcuts;
    QList<QKeySequence> voiceShortcuts;

private:
    static QJsonObject toJson(const ShortcutsFile &keys);
    static ShortcutsFile fromJson(const QJsonObject &obj);

    static ShortcutsFile getDefault();

public:
    static bool checkNoConflict(const ShortcutsFile &sd, QPair<int, int> *first = nullptr,
                                QPair<int, int> *second = nullptr);
};

#endif // SHORTCUTSFILE_H
