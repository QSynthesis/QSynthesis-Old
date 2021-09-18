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
    case sJoin:
        aResult = "";
        break;
    case linearJoin:
        aResult = "s";
    case rJoin:
        aResult = "r";
        break;
    case jJoin:
        aResult = "j";
        break;
    }

    return aResult;
}

Qs::PitchPoint Qs::stringToPitchPoint(const QString &oString) {
    Qs::PitchPoint aResult;

    if (oString == "s") {
        aResult = linearJoin;
    } else if (oString == "r") {
        aResult = rJoin;
    } else if (oString == "j") {
        aResult = jJoin;
    } else {
        aResult = sJoin;
    }

    return aResult;
}
