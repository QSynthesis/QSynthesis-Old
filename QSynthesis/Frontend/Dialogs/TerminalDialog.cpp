#include "TerminalDialog.h"
#include "mainwindow.h"

TerminalDialog::TerminalDialog(QString dir, QWidget *parent)
    : BaseDialog(parent), workingDir(dir), batchFile(FILE_NAME_TEMP_BATCH) {
    init();
}

TerminalDialog::TerminalDialog(QString dir, QString temp, QWidget *parent)
    : BaseDialog(parent), workingDir(dir), batchFile(temp) {
    init();
}

TerminalDialog::~TerminalDialog() {
    qDebug() << "[Destruct]"
             << "TerminalDialog";
}

int TerminalDialog::exec() {
    if (runInCmd()) {
        setResult(0);
        return QDialog::exec();
    } else {
        return -1;
    }
}

void TerminalDialog::init() {
    // 窗口初始化
    setWindowFlags(Qt::WindowCloseButtonHint);

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

#ifdef _WIN32
    m_pRender = nullptr;
#endif
#ifdef linux
    m_pTerminal = nullptr;
#endif
#ifdef __APPLE__
    m_pTerminal = nullptr;
#endif
}

bool TerminalDialog::runInCmd() {
    QString tempPath = QDir::toNativeSeparators(workingDir + Slash + batchFile);
    QString workingDir = QDir::toNativeSeparators(this->workingDir);

    std::wstring ws_bat = tempPath.toStdWString();
    std::wstring ws_dir = workingDir.toStdWString();

#ifdef _WIN32
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
#endif
#ifdef linux
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &TerminalDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(workingDir);
    m_pTerminal->start("/bin/bash", {tempPath});
#endif
#ifdef __APPLE__
    qDebug() << workingDir;
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &TerminalDialog::onProcessFinished);
    QString cmdStr = QString("   set status to do script \"cd %1 && ./temp.sh && exit\"\n").arg(workingDir);
    QString script = "tell application \"Terminal\"\n"
                     "   activate\n"
                     + cmdStr +
                     "   repeat until busy of status is false\n"
                     "       delay 1\n"
                     "   end repeat\n"
                     "   tell application \"Terminal\"\n"
                     "      quit\n"
                     "   end tell\n"
                     "end tell\n";
    QStringList processArguments;
    processArguments << "-l" << "AppleScript";
    QString osascript = "/usr/bin/osascript";
    m_pTerminal->start(osascript, processArguments);
    m_pTerminal->write(script.toUtf8());
    m_pTerminal->closeWriteChannel();
#endif
    return true;
}

QString TerminalDialog::getWorkingDir() const {
    return workingDir;
}

void TerminalDialog::setWorkingDir(const QString &value) {
    workingDir = value;
}

QString TerminalDialog::getBatchFile() const {
    return batchFile;
}

void TerminalDialog::setBatchFile(const QString &value) {
    batchFile = value;
}

void TerminalDialog::onTimer() {
#ifdef _WIN32
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
#ifdef linux
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onRenderOver();
#endif
#ifdef __APPLE__
    qDebug() << exitStatus << exitCode;
    if (exitStatus == QProcess::ExitStatus::NormalExit) {
        delete m_pTerminal;
        m_pTerminal = nullptr;
        onRenderOver();
    }
#endif
}

bool TerminalDialog::killProcess() {
#ifdef _WIN32
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
#endif
#ifdef linux
    if (m_pTerminal) {
        m_pTerminal->terminate();

        delete m_pTerminal;
        m_pTerminal = nullptr;
    }
#endif
#ifdef __APPLE__
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
#ifdef __APPLE__
    m_pTerminal->terminate();
    m_pTerminal->close();
    e_pTerminal = new QProcess(this);
    QString script = "tell application \"Terminal\"\n"
                     "   quit\n"
                     "end tell\n";
    QStringList processArguments;
    processArguments << "-l" << "AppleScript";
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
