#include "BackstageDialog.h"
#include "BackstageDialogs/ConcatenateWork.h"
#include "BackstageDialogs/ResampleWork.h"
#include "QUtils.h"

#include <QMessageBox>
#include <QThread>
#include <cmath>

BackstageDialog::BackstageDialog(QString dir, QWidget *parent)
    : BaseDialog(parent), m_workingDir(dir), m_threadCount(1) {
    init();
}

BackstageDialog::BackstageDialog(QString dir, int threads, QWidget *parent)
    : BaseDialog(parent), m_workingDir(dir), m_threadCount(threads) {
    init();
}

BackstageDialog::~BackstageDialog() {
}

int BackstageDialog::exec() {
    setResult(0);

    if (totalCount() == 0) {
        return 1;
    }

    QDir cacheDir(PathFindUpper(m_args.front().resamplerArgs.outFile()));
    if (!cacheDir.exists()) {
        cacheDir.mkpath(cacheDir.path());
    }

    QFile tempFile(m_workingDir + Slash + PathFindFileName(m_args.front().wavtoolArgs.outFile()));
    if (tempFile.exists()) {
        tempFile.remove();
    }

    prepareResampling();

    return BaseDialog::exec();
}

void BackstageDialog::init() {
    // 窗口初始化
    setWindowTitle(MainTitle);
    setFixedSize(420, 140);

    // 添加标签和按钮
    lbCaption = new QLabel(tr("Rendering..."), this);
    lbProcess = new QLabel(tr("Loading..."), this);
    btnCancel = new QPushButton(tr("Cancel"), this);

    lbCaption->move(25, 25);
    lbProcess->move(25, 55);

    lbProcess->setGeometry(lbProcess->x(), lbProcess->y(), width() - lbProcess->x(),
                           lbProcess->height());

    btnCancel->setFixedSize(115, 35);
    btnCancel->move(width() - btnCancel->width() - 15, height() - btnCancel->height() - 15);

    btnCancel->setFocus();
    btnCancel->setDefault(true);

    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    m_status = Loading;

    connect(btnCancel, &QPushButton::clicked, this, &BackstageDialog::onCancelClicked);
}

QList<RenderArgs> BackstageDialog::args() const {
    return m_args;
}

void BackstageDialog::setArgs(const QList<RenderArgs> &args) {
    m_args = args;
}

int BackstageDialog::threads() const {
    return m_threadCount;
}

void BackstageDialog::setThreads(int threads) {
    m_threadCount = threads;
}

int BackstageDialog::totalCount() const {
    return m_args.size();
}

QString BackstageDialog::workingDir() const {
    return m_workingDir;
}

void BackstageDialog::setWorkingDir(const QString &workingDir) {
    m_workingDir = workingDir;
}

void BackstageDialog::prepareResampling() {
    for (int j = 0; j < qMin(m_threadCount, totalCount()); ++j) {
        QThread *thread = new QThread(this);
        int count = 0;
        for (int i = j; i < totalCount(); i += m_threadCount) {
            ResampleWork *work = new ResampleWork();
            work->setWorkingDir(m_workingDir);
            work->setResampler(m_args.at(i).resamplerPath);
            work->setArgs(m_args.at(i).resamplerArgs);

            work->moveToThread(thread);

            connect(thread, &QThread::started, work, &ResampleWork::start);
            connect(work, &ResampleWork::finished, this, &BackstageDialog::handleResampleOver);

            count++;
            m_resampleWorks.append(work);
        }
        m_threads.insert(thread, qMakePair(0, count));
    }

    m_resampleCount = 0;
    m_status = Resampling;

    updateProcessCaption();

    for (auto it = m_threads.begin(); it != m_threads.end(); ++it) {
        QThread *thread = it.key();
        thread->start();
    }
}

void BackstageDialog::prepareConcatenating() {
    QThread *thread = new QThread(this);

    for (int i = 0; i < totalCount(); i++) {
        ConcatenateWork *work = new ConcatenateWork();
        work->setWorkingDir(m_workingDir);
        work->setWavtool(m_args.at(i).wavtoolPath);
        work->setArgs(m_args.at(i).wavtoolArgs);

        work->moveToThread(thread);

        if (i == 0) {
            connect(thread, &QThread::started, work, &ConcatenateWork::start);
        } else {
            ConcatenateWork *prevWork = m_concatenateWorks.back();
            connect(prevWork, &ConcatenateWork::finished, work, &ConcatenateWork::start);
        }

        connect(work, &ConcatenateWork::finished, this, &BackstageDialog::handleConcatenateOver);
        connect(work, &ConcatenateWork::crashed, this, &BackstageDialog::handleConcatenateOver);

        m_concatenateWorks.append(work);
    }
    m_threads.insert(thread, qMakePair(0, totalCount()));

    m_concatenateCount = 0;
    m_status = Concatenating;

    updateProcessCaption();

    for (auto it = m_threads.begin(); it != m_threads.end(); ++it) {
        QThread *thread = it.key();
        thread->start();
    }
}

void BackstageDialog::combineTempFiles() {
    QString tempAudioName = m_args.front().wavtoolArgs.outFile();

    QString whdFileName = m_workingDir + Slash + tempAudioName + ".whd";
    QString datFileName = m_workingDir + Slash + tempAudioName + ".dat";
    QString targetFileName = m_workingDir + Slash + tempAudioName;

    if (isFileExist(whdFileName) && isFileExist(datFileName)) {
        CombineFile(whdFileName, datFileName, targetFileName);
        RemoveFile(whdFileName);
        RemoveFile(datFileName);
    }
}

void BackstageDialog::removeAllThreads() {
    for (auto it = m_threads.begin(); it != m_threads.end(); ++it) {
        QThread *thread = it.key();
        if (thread->isRunning()) {
            thread->wait();
        }
        thread->deleteLater();
    }
    m_threads.clear();
}

void BackstageDialog::handleResampleOver() {
    ResampleWork *work = qobject_cast<ResampleWork *>(sender());
    QThread *thread = work->thread();

    m_resampleWorks.removeOne(work);
    work->deleteLater();

    auto it = m_threads.find(thread);
    if (it == m_threads.end()) {
        return;
    }

    QPair<int, int> &target = it.value();

    target.first++;
    m_resampleCount++;

    if (target.first == target.second) {
        thread->quit();
        qDebug() << "Thread Finished" << thread;
    }

    updateProcessCaption();

    if (m_resampleCount == totalCount()) {
        removeAllThreads();

        if (m_status == Resampling) {
            prepareConcatenating();
        } else if (m_status == Terminating) {
            close();
        }
    }
}

void BackstageDialog::handleConcatenateOver() {
    ConcatenateWork *work = qobject_cast<ConcatenateWork *>(sender());
    QThread *thread = work->thread();

    m_concatenateWorks.removeOne(work);
    work->deleteLater();

    m_concatenateCount++;
    updateProcessCaption();

    if (m_concatenateCount == totalCount()) {
        thread->quit();
        removeAllThreads();

        if (m_status == Concatenating) {
            combineTempFiles();
            onRenderOver();
        } else if (m_status == Terminating) {
            close();
        }
    }
}

void BackstageDialog::updateProcessCaption() {
    switch (m_status) {
    case Resampling: {
        QString textResampler = tr("Resample Process: ");
        lbProcess->setText(textResampler + QString::number(m_resampleCount) + "/" +
                           QString::number(totalCount()));
        break;
    }
    case Concatenating: {
        QString textWavtool = tr("Concatenate Process: ");
        lbProcess->setText(textWavtool + QString::number(m_concatenateCount) + "/" +
                           QString::number(totalCount()));
        break;
    }
    case Terminating: {
        lbProcess->setText("Attempt to end render...");
        break;
    }
    default: {
        lbProcess->setText(tr("Loading..."));
        break;
    }
    }
}

bool BackstageDialog::killProcess() {
    if (m_resampleWorks.isEmpty() && m_concatenateWorks.isEmpty()) {
        return false;
    }

    m_status = Terminating;
    for (ResampleWork *work : m_resampleWorks) {
        work->terminate();
    }
    for (ConcatenateWork *work : m_concatenateWorks) {
        work->terminate();
    }

    return true;
}

void BackstageDialog::onRenderOver() {
    setResult(1);
    close();
}

void BackstageDialog::onCancelClicked() {
    setResult(-1);
    close();
}

void BackstageDialog::closeEvent(QCloseEvent *event) {
    if (killProcess()) {
        event->ignore();
        return;
    }
    event->accept();
}
