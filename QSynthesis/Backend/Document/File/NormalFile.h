#ifndef NORMALFILE_H
#define NORMALFILE_H

#include "FileManager.h"

#include <QByteArray>
#include <QFile>

class NormalFile : public FileManager {
    Q_OBJECT
public:
    explicit NormalFile(QObject *parent = nullptr);
    explicit NormalFile(const QString &filename, QObject *parent = nullptr);
    virtual ~NormalFile();

    void setData(const QByteArray &data);
    QByteArray data() const;

protected:
    bool loadCore(bool *valid = nullptr) override;
    bool saveCore() override;

    void resetCore() override;

    QByteArray m_data;
};

#endif // NORMALFILE_H
