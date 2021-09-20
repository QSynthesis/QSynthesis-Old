#include "TerminalDialog.h"
#include "mainwindow.h"

TerminalDialog::TerminalDialog(QString dir, QWidget *parent)
    : BaseDialog(parent), m_workingDir(dir), m_batchFile(FILE_NAME_TEMP_BATCH) {
    init();
}

TerminalDialog::TerminalDialog(QString dir, QString temp, QWidget *parent)
    : BaseDialog(parent), m_workingDir(dir), m_batchFile(temp) {
    init();
}

TerminalDialog::~TerminalDialog() {
    qDebug() << "[Destruct]"
             << "TerminalDialog";
}

int TerminalDialog::exec() {
    if (runInCmd()) {
        setResult(0);
        return BaseDialog::exec();
    } else {
        return -1;
    }
}

void TerminalDialog::init() {
    // 窗口初始化
    setWindowTitle(MainTitle);
    setFixedSize(420, 140);

    // 添加标签和按钮
    lbCaption = new QLabel(tr("Rendering..."), this);
    btnCancel = new QPushButton(tr("Cancel"), this);

    lbCaption->move(25, 25);

    btnCancel->setFixedSize(115, 35);
    btnCancel->move(width() - btnCancel->width() - 15, height() - btnCancel->height() - 15);

    btnCancel->setFocus();
    btnCancel->setDefault(true);

    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(btnCancel, &QPushButton::clicked, this, &TerminalDialog::onCancelClicked);

#ifdef Q_OS_WINDOWS
    m_pRender = nullptr;
#endif
#ifdef Q_OS_LINUX
    m_pTerminal = nullptr;
#endif
#ifdef Q_OS_MAC
    m_pTerminal = nullptr;
    e_pTerminal = nullptr;
#endif
}

bool TerminalDialog::runInCmd() {
    QString tempPath = QDir::toNativeSeparators(m_workingDir + Slash + m_batchFile);
    QString workingDir = QDir::toNativeSeparators(m_workingDir);

    std::wstring ws_bat = tempPath.toStdWString();
    std::wstring ws_dir = workingDir.toStdWString();

#ifdef Q_OS_WINDOWS
    //------------------------------------------------------------------------
    m_pRender = new PROCESS_INFORMATION();

    PROCESS_INFORMATION &proInfo = *m_pRender;
    STARTUPINFO startInfo;

    memset(&startInfo, 0, sizeof(startInfo));
    memset(&proInfo, 0, sizeof(proInfo));
    startInfo.cb = sizeof(startInfo);

    // Execute Process
    BOOL bRet = CreateProcess(NULL, (LPWSTR) ws_bat.c_str(), NULL, NULL, FALSE,
                              CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, NULL, ws_dir.c_str(),
                              &startInfo, &proInfo);
    if (bRet == FALSE) {
        return false;
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TerminalDialog::onTimer);
    timer->start(100);

    //------------------------------------------------------------------------
#elif defined(Q_OS_LINUX)
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &TerminalDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(workingDir);
    m_pTerminal->start("/bin/bash", {tempPath});
#elif defined(Q_OS_MAC)
    qDebug() << workingDir;
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &TerminalDialog::onProcessFinished);
    QString cmdStr =
        QString("set status to do script \"cd %1 && ./temp.sh && exit\" in window 1\n").arg(workingDir);
    QString cmdInNewWindowStr =
        QString("set status to do script \"cd %1 && ./temp.sh && exit\"\n").arg(workingDir);
    QString script = "tell application \"Terminal\"\n"
                     "   if (count of windows) is not 0 then\n"
                     "      if busy of window 1 is false then\n"
                                + cmdStr +
                     "      else\n"
                                + cmdInNewWindowStr +
                     "      end if\n"
                     "   else\n"
                            + cmdInNewWindowStr +
                     "   end if\n"
                     "   activate\n"
                     "   repeat\n"
                     "       delay 1\n"
                     "       if not busy of status then exit repeat\n"
                     "   end repeat\n"
                     "   quit window 1\n"
                     "end tell\n";
    QStringList processArguments;
    processArguments << "-l"
                     << "AppleScript";
    QString osascript = "/usr/bin/osascript";
    m_pTerminal->start(osascript, processArguments);
    m_pTerminal->write(script.toUtf8());
    m_pTerminal->closeWriteChannel();
#endif
    return true;
}

QString TerminalDialog::workingDir() const {
    return m_workingDir;
}

void TerminalDialog::setWorkingDir(const QString &value) {
    m_workingDir = value;
}

QString TerminalDialog::batchFile() const {
    return m_batchFile;
}

void TerminalDialog::setBatchFile(const QString &value) {
    m_batchFile = value;
}

void TerminalDialog::onTimer() {
#ifdef Q_OS_WINDOWS
    if (m_pRender) {
        DWORD exitCode;
        GetExitCodeProcess(m_pRender->hProcess, &exitCode);

        if (exitCode != STILL_ACTIVE) {
            CloseHandle(m_pRender->hProcess);
            CloseHandle(m_pRender->hThread);

            timer->stop();

            delete m_pRender;
            m_pRender = nullptr;

            onRenderOver();
        }
    }
#endif
}

void TerminalDialog::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
#ifdef Q_OS_LINUX
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onRenderOver();
#elif defined(Q_OS_MAC)
    qDebug() << exitStatus << exitCode;
    if (exitStatus == QProcess::ExitStatus::NormalExit) {
        delete m_pTerminal;
        m_pTerminal = nullptr;
        onRenderOver();
    }
#endif
}

bool TerminalDialog::killProcess() {
#ifdef Q_OS_WINDOWS
    if (m_pRender) {
        DWORD exitCode = 0;
        GetExitCodeProcess(m_pRender->hProcess, &exitCode);

        if (exitCode == STILL_ACTIVE) {
            if (!TerminateProcess(m_pRender->hProcess, exitCode)) {
                qDebug() << "Fail to terminate process.";
                return 0;
            }
        }

        if (timer) {
            timer->stop();
        }

        CloseHandle(m_pRender->hProcess);
        CloseHandle(m_pRender->hThread);

        delete m_pRender;
        m_pRender = nullptr;
    }
#elif defined(Q_OS_LINUX)
    if (m_pTerminal) {
        m_pTerminal->terminate();

        delete m_pTerminal;
        m_pTerminal = nullptr;
    }
#elif defined(Q_OS_MAC)
    if (m_pTerminal) {
        m_pTerminal->terminate();
        m_pTerminal->close();
        delete m_pTerminal;
        m_pTerminal = nullptr;
        delete e_pTerminal;
        e_pTerminal = nullptr;
    }
#endif
    return 1;
}

void TerminalDialog::onRenderOver() {
    setResult(1);
    close();
}

void TerminalDialog::onCancelClicked() {
    setResult(-1);
#ifdef Q_OS_MAC
    m_pTerminal->terminate();
    m_pTerminal->close();
    e_pTerminal = new QProcess(this);
    QString script = "tell application \"Terminal\"\n"
                     "   quit\n"
                     "end tell\n";
    QStringList processArguments;
    processArguments << "-l"
                     << "AppleScript";
    QString osascript = "/usr/bin/osascript";
    e_pTerminal->start(osascript, processArguments);
    e_pTerminal->write(script.toUtf8());
    e_pTerminal->closeWriteChannel();
    e_pTerminal->waitForFinished();
#endif
    close();
}

void TerminalDialog::closeEvent(QCloseEvent *event) {
    if (!killProcess()) {
        QString content = tr("Fail to stop rendering.");

        QMessageBox::warning(this, MainTitle, content);

        event->ignore();
        return;
    }

    event->accept();
}
