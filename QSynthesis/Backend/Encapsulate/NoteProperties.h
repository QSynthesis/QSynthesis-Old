#ifndef NOTEPROPERTIES_H
#define NOTEPROPERTIES_H

#include <QString>

struct NoteProperties {
    NoteProperties();
    void clear();

    QString length;
    QString intensity;
    QString modulation;

    QString preUttr;
    QString overlap;

    QString tempo;

    QString flags;
    QString velocity;
    QString startpoint;

    QString preUttrOto;
    QString overlapOto;
};

#endif // NOTEPROPERTIES_H
