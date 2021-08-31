#ifndef SCRIPTPLUGINDIALOG_H
#define SCRIPTPLUGINDIALOG_H

#include <QCloseEvent>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "BaseDialog.h"

#ifdef WIN32
#include "Windows.h"
#endif
#ifdef linux
#endif

class ScriptPluginDialog : public BaseDialog {
    Q_OBJECT
public:
    explicit ScriptPluginDialog(QString tmpFile, QString exeFile, QString workingDir,
                                QWidget *parent = nullptr);

    ~ScriptPluginDialog();

    int exec() override;

    bool runInCmd();

protected:
    QString m_tmpFile;
    QString m_exeFile;
    QString m_workingDir;

    QPushButton *btnCancel;
    QLabel *lbCaption;

#ifdef WIN32
    SHELLEXECUTEINFO *m_pRender;
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

#endif // SCRIPTPLUGINDIALOG_H
