#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>
#include <QWidget>

#include "Backend/Render/ResamplerArgs.h"
#include "Backend/Render/WavtoolArgs.h"
#include "BaseDialog.h"
#include "QUtils.h"

#ifdef WIN32
#include "Windows.h"
#endif
#ifdef linux
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

    QString getWorkingDir() const;
    void setWorkingDir(const QString &value);

    QString getBatchFile() const;
    void setBatchFile(const QString &value);

protected:
    QString workingDir;
    QString batchFile;

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
