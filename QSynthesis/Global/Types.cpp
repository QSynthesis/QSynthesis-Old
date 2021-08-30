#include "Types.h"

QString Qs::NoteStatusToString(Qs::NoteStatus status) {
    QString name;

    switch (status) {
    case Rest:
        name = "rest";
        break;
    case Listed:
        name = "listed";
        break;
    case Unlisted:
        name = "unlisted";
        break;
    }

    return name;
}

QString Qs::pitchPointToString(const Qs::PitchPoint &oType) {

    QString aResult;
    switch (oType) {
    case sType:
        aResult = "";
        break;
    case lineType:
        aResult = "s";
    case rType:
        aResult = "r";
        break;
    case jType:
        aResult = "j";
        break;
    }

    return aResult;
}

Qs::PitchPoint Qs::stringToPitchPoint(const QString &oString) {
    Qs::PitchPoint aResult;

    if (oString == "s") {
        aResult = lineType;
    } else if (oString == "r") {
        aResult = rType;
    } else if (oString == "j") {
        aResult = jType;
    } else {
        aResult = sType;
    }

    return aResult;
}
