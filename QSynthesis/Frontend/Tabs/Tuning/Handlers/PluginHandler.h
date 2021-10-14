#ifndef PLUGINHANDLER_H
#define PLUGINHANDLER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>

#include "Note/QLinkNote.h"
#include "PluginInfo.h"
#include "SequenceTextFiles/SequenceTextData.h"
#include "Structures/Transfer/PluginTempData.h"

class PluginHandler : public QObject {
    Q_OBJECT
public:
    explicit PluginHandler(PluginTempData &data, const PluginInfo &plugin,
                           const QString &workingDir, QWidget *parent = nullptr);
    ~PluginHandler();

public:
    int exec();

private:
    const PluginInfo &plugin;
    PluginTempData &data;

    QString workingDir;
    QString tmpPath;

    int stateCode;

    bool writeFile();
    bool readFile();

    bool parseSectionName(const QString &oName, QString &oResult);
    bool parseSectionNote(const QStringList &oSectionList, QLinkNote &oNote);

    void writeSectionName(const int &oName, QTextStream &oStream);
    void writeSectionName(const QString &oName, QTextStream &oStream);

    void writeSectionNote(int num, const QLinkNote &oNote, const NoteReadonlys &oReadonly,
                          QTextStream &oStream);
    void writeSectionSettings(QTextStream &oStream);
    void writeSectionVersion(QTextStream &oStream);
};

#endif // PLUGINHANDLER_H
