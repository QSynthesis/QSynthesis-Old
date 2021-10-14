#include "InfoTextOperation.h"

InfoTextOperation::InfoTextOperation() {
    m_typeN = InfoText;
}

InfoTextOperation::InfoTextOperation(InfoTextOperation::Property prop) {
    m_typeN = InfoText;
    m_property = prop;
}

QString InfoTextOperation::origin() const {
    return m_origin;
}

void InfoTextOperation::setOrigin(const QString &origin) {
    m_origin = origin;
}

QString InfoTextOperation::modified() const {
    return m_modified;
}

void InfoTextOperation::setModified(const QString &modified) {
    m_modified = modified;
}

InfoTextOperation::Property InfoTextOperation::property() const {
    return m_property;
}

void InfoTextOperation::setProperty(const Property &property) {
    m_property = property;
}

bool InfoTextOperation::differ() const {
    return m_origin != m_modified;
}
