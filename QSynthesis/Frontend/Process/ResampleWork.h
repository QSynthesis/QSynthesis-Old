#ifndef RESAMPLEWORK_H
#define RESAMPLEWORK_H

#include "BaseWork.h"
#include "Render/ResamplerArgs.h"

class ResampleWork : public BaseWork {
    Q_OBJECT
public:
    explicit ResampleWork(QObject *parent = nullptr);
    ~ResampleWork();

protected:
    void startCore() override;

public:
    QString workingDir() const;
    void setWorkingDir(const QString &workingDir);

    QString resampler() const;
    void setResampler(const QString &resampler);

    ResamplerArgs args() const;
    void setArgs(const ResamplerArgs &args);

    bool skipExist() const;
    void setSkipExist(bool skipExist);

private:
    QString m_workingDir;
    QString m_resampler;
    ResamplerArgs m_args;

    bool m_skipExist;
};

#endif // RESAMPLEWORK_H
