#ifndef QFILESET_H
#define QFILESET_H

#include <QDir>
#include <QSet>

class QFileSet {
public:
    enum Type { File, Directory };

    QFileSet();
    QFileSet(Type type);

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

#endif // QFILESET_H
