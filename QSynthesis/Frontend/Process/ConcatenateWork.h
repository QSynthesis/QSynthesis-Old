#ifndef CONCATENATEWORK_H
#define CONCATENATEWORK_H

#include "BaseWork.h"
#include "QUtauRender.h"

class ConcatenateWork : public BaseWork {
    Q_OBJECT
public:
    explicit ConcatenateWork(QObject *parent = nullptr);
    ~ConcatenateWork();

protected:
    void startCore() override;

public:
    QString workingDir() const;
    void setWorkingDir(const QString &workingDir);

    QString wavtool() const;
    void setWavtool(const QString &wavtool);

    WavtoolArgs args() const;
    void setArgs(const WavtoolArgs &args);

private:
    QString m_workingDir;
    QString m_wavtool;
    WavtoolArgs m_args;
};

#endif // CONCATENATEWORK_H
