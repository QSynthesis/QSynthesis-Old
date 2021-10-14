#ifndef BASEDIRINFO_H
#define BASEDIRINFO_H

#include "BaseFile.h"

class BaseDirInfo : public BaseFile {
public:
    BaseDirInfo();
    virtual ~BaseDirInfo();

protected:
    BaseDirInfo(Qs::VariableSource source);

public:
    QString filename() const override;
    void setFilename(const QString &filename) = delete;

    QString dirname() const;
    void setDirname(const QString &dirname);

protected:
    virtual QString infoFilename() const;
};

#endif // BASEDIRINFO_H
