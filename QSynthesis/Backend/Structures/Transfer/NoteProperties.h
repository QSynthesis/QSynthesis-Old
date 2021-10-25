#ifndef NOTEPROPERTIES_H
#define NOTEPROPERTIES_H

#include <QString>

class NoteProperties {
public:
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
