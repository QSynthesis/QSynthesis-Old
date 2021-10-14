#include "TrackModifyOperation.h"

TrackModifyOperation::TrackModifyOperation(Change change) {
    m_typeT = Modify;

    m_change = change;
}

QString TrackModifyOperation::origin() const {
    return m_origin;
}

void TrackModifyOperation::setOrigin(const QString &origin) {
    m_origin = origin;
}

QString TrackModifyOperation::modified() const {
    return m_modified;
}

void TrackModifyOperation::setModified(const QString &modified) {
    m_modified = modified;
}

TrackModifyOperation::Change TrackModifyOperation::change() const {
    return m_change;
}

bool TrackModifyOperation::differ() const {
    return m_origin != m_modified;
}
