#ifndef PLUGINTEMPDATA_H
#define PLUGINTEMPDATA_H

#include <QObject>

#include "NoteReadonlys.h"
#include "QUtauSections.h"

class PluginTempData {
public:
    PluginTempData();

    QString project;

    SectionSettings sectionSettings;
    SectionVersion sectionVersion;

    QVector<QLinkNote> notes;
    QVector<NoteReadonlys> readonlys;

    bool hasPrev;
    bool hasNext;

    int start; // Serial number of beginning note

    int normalSize() const;
    int normalBegin() const;
    int normalEnd() const;

    friend QDebug operator<<(QDebug debug, const PluginTempData &ns);
};

#endif // PLUGINTEMPDATA_H
