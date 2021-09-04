#include "ExecutePluginDialog.h"
#include "mainwindow.h"

ExecutePluginDialog::ExecutePluginDialog(QString tmpFile, QString exeFile, QString workingDir,
                                         QWidget *parent)
    : BaseDialog(parent), m_tmpFile(tmpFile), m_exeFile(exeFile), m_workingDir(workingDir) {
    init();
}

ExecutePluginDialog::~ExecutePluginDialog() {
    qDebug() << "[Destruct]"
             << "ExecutePluginDialog";
}

int ExecutePluginDialog::exec() {
    if (runInCmd()) {
        setResult(0);
        return BaseDialog::exec();
    } else {
        return -1;
    }
}

void ExecutePluginDialog::init() {
    // 窗口初始化
    setWindowTitle(MainTitle);
    setFixedSize(420, 140);

    // 添加标签和按钮

    lbCaption = new QLabel(tr("Plug-in running..."), this);
    btnCancel = new QPushButton(tr("Cancel"), this);

    lbCaption->move(25, 25);

    btnCancel->setFixedSize(115, 35);
    btnCancel->move(width() - btnCancel->width() - 15, height() - btnCancel->height() - 15);

    btnCancel->setFocus();
    btnCancel->setDefault(true);

    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(btnCancel, &QPushButton::clicked, this, &ExecutePluginDialog::onCancelClicked);

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

bool ExecutePluginDialog::runInCmd() {
    QString tempPath = m_tmpFile;
    QString execPath = m_exeFile;

    if (tempPath.contains(' ')) {
        tempPath = "\"" + tempPath + "\"";
    }
    if (execPath.contains(' ')) {
        execPath = "\"" + execPath + "\"";
    }

    QString cmdLine = execPath + " " + tempPath;

    std::wstring ws_exe = cmdLine.toStdWString();
    std::wstring ws_dir = m_workingDir.toStdWString();

#ifdef _WIN32
    //------------------------------------------------------------------------
    m_pRender = new PROCESS_INFORMATION();

    PROCESS_INFORMATION &proInfo = *m_pRender;
    STARTUPINFO startInfo;

    memset(&startInfo, 0, sizeof(startInfo));
    memset(&proInfo, 0, sizeof(proInfo));
    startInfo.cb = sizeof(startInfo);

    // Execute Process
    BOOL bRet = CreateProcess(NULL, (LPWSTR) ws_exe.c_str(), NULL, NULL, FALSE,
                              CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, NULL, ws_dir.c_str(),
                              &startInfo, &proInfo);
    if (bRet == FALSE) {
        return false;
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ExecutePluginDialog::onTimer);
    timer->start(100);

    //------------------------------------------------------------------------
#endif
#ifdef linux
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &ExecutePluginDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(m_workingDir);
    m_pTerminal->start(execPath, {tempPath});
#endif
#ifdef __APPLE__
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &ExecutePluginDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(m_workingDir);
    m_pTerminal->start(execPath, {tempPath});
#endif
    return true;
}


void ExecutePluginDialog::onTimer() {
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

            onPluginExited();
        }
    }
#endif
}

void ExecutePluginDialog::onPluginExited() {
    setResult(1);
    close();
}

void ExecutePluginDialog::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
#ifdef linux
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onPluginExited();
#endif
#ifdef __APPLE__
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onPluginExited();
#endif
}

void ExecutePluginDialog::onCancelClicked() {
    close();
}
