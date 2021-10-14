#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "BaseDialog.h"
#include "QUtils.h"
#include "Render/ResamplerArgs.h"
#include "Render/WavtoolArgs.h"

#ifdef Q_OS_WINDOWS
#include "Windows.h"
#endif
#ifdef Q_OS_LINUX
#include <unistd.h>
#endif

class TerminalDialog : public BaseDialog {
    Q_OBJECT
public:
    explicit TerminalDialog(QString dir, QWidget *parent = nullptr);
    explicit TerminalDialog(QString dir, QString temp, QWidget *parent = nullptr);

    ~TerminalDialog();

    int exec() override;

    bool runInCmd();

    QString workingDir() const;
    void setWorkingDir(const QString &value);

    QString batchFile() const;
    void setBatchFile(const QString &value);

protected:
    QString m_workingDir;
    QString m_batchFile;

    QPushButton *btnCancel;
    QLabel *lbCaption;

#ifdef WIN32
    PROCESS_INFORMATION *m_pRender;
#elif defined(Q_OS_LINUX)
    QProcess *m_pTerminal;
#elif defined(Q_OS_MAC)
    QProcess *m_pTerminal;
    QProcess *e_pTerminal;
#endif

    QTimer *timer;

private:
    void init();

    void onTimer();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    bool killProcess();
    void onRenderOver();

    void onCancelClicked();

    void closeEvent(QCloseEvent *event) override;
};

#endif // TERMINALDIALOG_H
