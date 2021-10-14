#ifndef NOTEREADONLYS_H
#define NOTEREADONLYS_H

#include <QString>

#include "QUtauConstants.h"

struct NoteReadonlys {
    double preuttr;
    double overlap;
    double stpoint;
    QString filename;
    QString alias;
    QString cache;

    NoteReadonlys();
};

#endif // NOTEREADONLYS_H
