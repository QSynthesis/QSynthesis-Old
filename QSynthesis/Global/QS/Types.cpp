#include "Types.h"

QString Qs::noteStatusToString(Qs::NoteStatus status) {
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

QString Qs::buttonStatusToString(Qs::ButtonStatus status) {
    QString name;
    switch (status) {
    case RollOut:
        name = "rollOut";
        break;
    case RollOver:
        name = "rollOver";
        break;
    case RollDown:
        name = "rollDown";
        break;
    }
    return name;
}
