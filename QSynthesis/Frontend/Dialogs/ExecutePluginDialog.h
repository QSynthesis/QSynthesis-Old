#ifndef EXECUTEPLUGINDIALOG_H
#define EXECUTEPLUGINDIALOG_H

#include <QCloseEvent>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#ifdef WIN32
#include "Windows.h"
#endif
#ifdef linux
#include <unistd.h>
#endif

class ExecutePluginDialog : public QDialog {
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
#endif
#ifdef linux
    QProcess *m_pTerminal;
#endif
#ifdef __APPLE__
    QProcess *m_pTerminal;
#endif

    QTimer *timer;

private:
    void init();

    void onTimer();

    void onPluginExited();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void onCancelClicked();
    void closeEvent(QCloseEvent *event) override;
};

#endif // EXECUTEPLUGINDIALOG_H
