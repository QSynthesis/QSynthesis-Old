#ifndef SECTIONVERSION_H
#define SECTIONVERSION_H

#include <QDebug>
#include <QString>

// Project File Version
class SectionVersion {
public:
    SectionVersion();
    void clear();

    QString version;
    QString charset;

    bool operator==(const SectionVersion &another) const;
    bool operator!=(const SectionVersion &another) const;
};

#endif // SECTIONVERSION_H
