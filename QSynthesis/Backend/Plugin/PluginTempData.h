#ifndef PLUGINTEMPDATA_H
#define PLUGINTEMPDATA_H

#include <QObject>

#include "../Note/QLinkNote.h"
#include "Document/SequenceTextFiles/SequenceTextData.h"

struct NoteReadonlys {
    double preuttr;
    double overlap;
    double stpoint;
    QString filename;
    QString alias;
    QString cache;

    NoteReadonlys() {
        preuttr = overlap = stpoint = NODEF_DOUBLE;
        filename = alias = cache = NODEF_STRING;
    }
};

struct PluginTempData {
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
