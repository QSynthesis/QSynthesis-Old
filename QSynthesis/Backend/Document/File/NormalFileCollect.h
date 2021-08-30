#ifndef NORMALFILECOLLECT_H
#define NORMALFILECOLLECT_H

#include "FileCollect.h"
#include "NormalFile.h"

class NormalFileCollect : public FileCollect {
    Q_OBJECT
public:
    explicit NormalFileCollect(QObject *parent = nullptr);
    explicit NormalFileCollect(QString dir, QObject *parent = nullptr);
    ~NormalFileCollect();

    QList<NormalFile *> files() const;

private:
    FileManager *addFileCore(const QString &filename) override;
};

#endif // NORMALFILECOLLECT_H
