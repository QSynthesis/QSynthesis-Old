#include "ScriptPluginDialog.h"
#include "mainwindow.h"

ScriptPluginDialog::ScriptPluginDialog(QString tmpFile, QString exeFile, QString workingDir,
                                       QWidget *parent)
    : BaseDialog(parent), m_tmpFile(tmpFile), m_exeFile(exeFile), m_workingDir(workingDir) {
    init();
}

ScriptPluginDialog::~ScriptPluginDialog() {
    qDebug() << "[Destruct]"
             << "ScriptPluginDialog";
}

int ScriptPluginDialog::exec() {
    if (runInCmd()) {
        setResult(0);
        return BaseDialog::exec();
    } else {
        return -1;
    }
}

void ScriptPluginDialog::init() {
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
    connect(btnCancel, &QPushButton::clicked, this, &ScriptPluginDialog::onCancelClicked);

#ifdef Q_OS_WINDOWS
    m_pRender = nullptr;
#endif
#ifdef linux
    m_pTerminal = nullptr;
#endif
#ifdef Q_OS_MAC
    m_pTerminal = nullptr;
#endif
}

bool ScriptPluginDialog::runInCmd() {
    QString tempPath = m_tmpFile;
    QString execPath = m_exeFile;

    if (tempPath.contains(' ')) {
        tempPath = "\"" + tempPath + "\"";
    }
    if (execPath.contains(' ')) {
        execPath = "\"" + execPath + "\"";
    }

    std::wstring ws_exe = execPath.toStdWString();
    std::wstring ws_tmp = tempPath.toStdWString();
    std::wstring ws_dir = m_workingDir.toStdWString();

#ifdef Q_OS_WINDOWS
    //------------------------------------------------------------------------
    m_pRender = new SHELLEXECUTEINFO();

    SHELLEXECUTEINFO &ShExecInfo = *m_pRender;

    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = ws_exe.c_str();
    ShExecInfo.lpParameters = ws_tmp.c_str();
    ShExecInfo.lpDirectory = ws_dir.c_str();
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;

    BOOL b_Ret = ShellExecuteEx(&ShExecInfo);
    if (!b_Ret) {
        return false;
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ScriptPluginDialog::onTimer);
    timer->start(100);

    //------------------------------------------------------------------------
#endif
#ifdef linux
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &ScriptPluginDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(m_workingDir);
    m_pTerminal->start(execPath, {tempPath});
#endif
#ifdef Q_OS_MAC
    m_pTerminal = new QProcess(this);
    connect(m_pTerminal, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &ScriptPluginDialog::onProcessFinished);

    m_pTerminal->setWorkingDirectory(m_workingDir);
    m_pTerminal->start(execPath, {tempPath});
#endif

    return true;
}


void ScriptPluginDialog::onTimer() {
#ifdef Q_OS_WINDOWS
    if (m_pRender) {
        DWORD exitCode;
        GetExitCodeProcess(m_pRender->hProcess, &exitCode);

        if (exitCode != STILL_ACTIVE) {
            CloseHandle(m_pRender->hProcess);

            timer->stop();

            delete m_pRender;
            m_pRender = nullptr;

            onPluginExited();
        }
    }
#endif
}

void ScriptPluginDialog::onPluginExited() {
    setResult(1);
    close();
}

void ScriptPluginDialog::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
#ifdef linux
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onPluginExited();
#endif
#ifdef Q_OS_MAC
    delete m_pTerminal;
    m_pTerminal = nullptr;

    onPluginExited();
#endif
}

void ScriptPluginDialog::onCancelClicked() {
    close();
}
