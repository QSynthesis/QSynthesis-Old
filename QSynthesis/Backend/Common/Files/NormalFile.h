#ifndef NORMALFILE_H
#define NORMALFILE_H

#include "BaseFile.h"

#include <QByteArray>
#include <QFile>

class NormalFile : public BaseFile {
public:
    NormalFile();
    NormalFile(const QString &filename);
    virtual ~NormalFile();

protected:
    NormalFile(Qs::VariableSource source); // Use by child class

public:
    void setData(const QByteArray &data);
    QByteArray data() const;

protected:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

    QByteArray m_data;
};

#endif // NORMALFILE_H
