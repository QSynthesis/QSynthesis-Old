#ifndef BACKSTAGEDIALOG_H
#define BACKSTAGEDIALOG_H

#include <QLabel>
#include <QMutex>
#include <QPushButton>

#include "QUtauRender.h"
#include "Widgets/BaseDialog.h"

class ResampleWork;
class ConcatenateWork;

class BackstageDialog : public BaseDialog {
    Q_OBJECT
public:
    enum Status { Resampling, Concatenating, Loading, Terminating };

    explicit BackstageDialog(QString dir, QWidget *parent = nullptr);
    explicit BackstageDialog(QString dir, int threads, QWidget *parent = nullptr);
    ~BackstageDialog();

    int exec() override;

private:
    void init();

public:
    QList<RenderArgs> args() const;
    void setArgs(const QList<RenderArgs> &args);

    int threads() const;
    void setThreads(int threads);

    int totalCount() const;

    QString workingDir() const;
    void setWorkingDir(const QString &workingDir);

private:
    QString m_workingDir;

    int m_threadCount;
    Status m_status;

    QList<RenderArgs> m_args;

    QHash<QThread *, QPair<int, int>> m_threads;
    QList<ResampleWork *> m_resampleWorks;
    QList<ConcatenateWork *> m_concatenateWorks;

    QMutex m_resampleLock;
    QMutex m_concatenateLock;

    int m_resampleCount;
    int m_concatenateCount;

    void prepareResampling();
    void prepareConcatenating();
    void combineTempFiles();

    void removeAllThreads();

    void handleResampleOver();
    void handleConcatenateOver();

    void updateProcessCaption();

private:
    QLabel *lbCaption, *lbProcess;

    QPushButton *btnCancel;

    bool killProcess();

    void onRenderOver();
    void onCancelClicked();

    void closeEvent(QCloseEvent *event) override;
};

#endif // BACKSTAGEDIALOG_H
