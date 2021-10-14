#ifndef EXECUTEPLUGINDIALOG_H
#define EXECUTEPLUGINDIALOG_H

#include <QCloseEvent>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "BaseDialog.h"

#ifdef Q_OS_WINDOWS
#include "Windows.h"
#elif defined(Q_OS_LINUX)
#include <unistd.h>
#endif

class ExecutePluginDialog : public BaseDialog {
    Q_OBJECT
public:
    explicit ExecutePluginDialog(QString tmpFile, QString exeFile, QString workingDir,
                                 QWidget *parent = nullptr);

    ~ExecutePluginDialog();

    int exec() override;

    bool runInCmd();

protected:
    QString m_tmpFile;
    QString m_exeFile;
    QString m_workingDir;

    QPushButton *btnCancel;
    QLabel *lbCaption;

#ifdef WIN32
    PROCESS_INFORMATION *m_pRender;
#elif defined(Q_OS_LINUX)
    QProcess *m_pTerminal;
#elif defined(Q_OS_MAC)
    QProcess *m_pTerminal;
#endif

    QTimer *timer;

private:
    void init();

    void onTimer();

    void onPluginExited();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void onCancelClicked();
};

#endif // EXECUTEPLUGINDIALOG_H
