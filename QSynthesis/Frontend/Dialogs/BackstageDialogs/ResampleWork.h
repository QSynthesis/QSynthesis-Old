#ifndef RESAMPLEWORK_H
#define RESAMPLEWORK_H

#include "BaseWork.h"
#include "Render/ResamplerArgs.h"

class ResampleWork : public BaseWork {
    Q_OBJECT
public:
    explicit ResampleWork(QObject *parent = nullptr);
    ~ResampleWork();

    void start() override;

public:
    QString workingDir() const;
    void setWorkingDir(const QString &workingDir);

    QString resampler() const;
    void setResampler(const QString &resampler);

    ResamplerArgs args() const;
    void setArgs(const ResamplerArgs &args);

private:
    QString m_workingDir;
    QString m_resampler;
    ResamplerArgs m_args;
};

#endif // RESAMPLEWORK_H
