#ifndef FILENAMESET_H
#define FILENAMESET_H

#include <QDir>
#include <QSet>

#include "QUtils.h"

class FileNameSet {
public:
    enum Type { File, Directory };

    FileNameSet();
    FileNameSet(Type type);

private:
    QStringList m_files;

    Type m_type;

public:
    void set(const QStringList &files);

    QStringList all() const;
    QStringList valid() const;

    void filter();

    bool push(const QString &s);
    bool unshift(const QString &s);

    void advance(const QString &s);
    bool remove(const QString &s);

    bool isEmpty() const;
    bool contains(const QString &s);

    void clear();

    Type type() const;
    void setType(const Type &type);
};

#endif // FILENAMESET_H
