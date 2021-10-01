#ifndef BASEFILE_H
#define BASEFILE_H

#include <QObject>

#include "Types.h"

class BaseFile {
public:
    BaseFile();
    BaseFile(const QString &filename);
    virtual ~BaseFile();

protected:
    BaseFile(Qs::VariableSource source); // Use by child class

public:
    bool load(bool *valid = nullptr);
    bool save();

    bool remove();

    void clear();
    void reset();

public:
    virtual QString filename() const;
    void setFilename(const QString &filename);

    bool exists() const;

protected:
    virtual bool loadCore(bool *valid = nullptr);
    virtual bool saveCore();

    virtual void resetCore();
    virtual void prepareCore();

    QString m_filename;
};

#endif // BASEFILE_H
