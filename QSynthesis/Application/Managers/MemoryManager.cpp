#include "MemoryManager.h"

MemoryManager::MemoryManager(QObject *parent) : QObject(parent) {
}

MemoryManager::~MemoryManager() {
    if (m_shared.attach()) {
        m_shared.detach();
    }
}

bool MemoryManager::load() {
    const QString tempDirPrefix = "qs";
    const QString tempMemoryPrefix = "QSynthesis_Memory_";
    int maxIndex = 1;

    // Normal path under windows is "C:\Users\{usename}\AppData\Local\Temp\"
    QString tempDirName = QDir::tempPath() + Slash + TempDirName;

    QDir tempDir(tempDirName);
    if (tempDir.exists()) {
        QFileInfoList flist = tempDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Time);

        for (QFileInfo &info : flist) {
            QString dirname = info.fileName();

            // Test prefix
            if (!dirname.startsWith(tempDirPrefix)) {
                continue;
            }
            dirname = dirname.mid(tempDirPrefix.size());

            // Test suffix
            bool isNum = false;
            int num = dirname.toInt(&isNum);
            if (!isNum) {
                continue;
            }
            if (num > maxIndex) {
                maxIndex = num;
            }

            // Test used
            QSharedMemory memory;
            memory.setKey(tempMemoryPrefix + QString::number(num));
            if (memory.attach()) {
                continue;
            }

            // When shared memory with key of dir name is not used
            qDebug() << info.absoluteFilePath();
        }
    } else if (!tempDir.mkdir(tempDirName)) {
        return false;
    }

    // Set shared memory
    m_shared.setKey(tempMemoryPrefix + QString::number(maxIndex + 1));
    m_shared.create(1);

    m_tempDir = tempDirName;
    return true;
}

QString MemoryManager::tempDir() const
{
    return m_tempDir;
}
