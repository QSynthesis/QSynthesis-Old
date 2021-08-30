#include "mainwindow.h"

void MainWindow::checkWorkingDir() {
    QString voice = voiceProfile();
    QString plugin = pluginsProfile();
    QString config = configProfile();

    QString themes = themesProfile();
    QString languages = languagesProfile();

    qDebug() << "Voice:" << voice;
    qDebug() << "Plugins:" << plugin;
    qDebug() << "Config:" << config;

    if (!isDirExist(voice)) {
        exitOnVoiceDirMissing();
    }
    if (!isDirExist(plugin)) {
        exitOnPluginsDirMissing();
    }
    if (!isDirExist(config)) {
        exitOnConfigDirMissing();
    } else {
        QDir dir;
        if (!dir.exists(themes)) {
            dir.mkpath(themes);
        }
        if (!dir.exists(languages)) {
            dir.mkpath(languages);
        }
    }
}

void MainWindow::checkTemporaryDir() {
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
        exitOnNoIOPermission();
    }

    // Set shared memory
    sharedMemory.setKey(tempMemoryPrefix + QString::number(maxIndex + 1));
    sharedMemory.create(1);

    tempDirectoryName = tempDirName;
}

void MainWindow::exitPreparation() {
    if (voice) {
        delete voice;
    }
    if (plugins) {
        delete plugins;
    }
    if (themes) {
        delete themes;
    }
    if (languages) {
        delete languages;
    }

    if (sharedMemory.attach()) {
        sharedMemory.detach();
    }
}
