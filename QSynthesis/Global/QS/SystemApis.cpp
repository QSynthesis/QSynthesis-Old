#include "SystemApis.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QProcess>

QTextCodec *GetUtfCodec(const QByteArray &data) {
    QTextCodec *autoCodec = QTextCodec::codecForUtfText(data);
    QString name = autoCodec->name();
    if (name == "ISO-8859-1") {
        return nullptr;
    } else {
        return autoCodec;
    }
}

QStringList FindRecursiveDirs(const QString &base) {
    QDir dir;
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setPath(base);

    if (!dir.exists()) {
        return {};
    }

    QDirIterator iter(dir, QDirIterator::Subdirectories);
    QStringList res;

    while (iter.hasNext()) {
        iter.next();
        QFileInfo aInfo = iter.fileInfo();
        res.append(aInfo.absoluteFilePath());
    }

    return res;
}


bool CopyFile(const QString &fileName, const QString &newName) {
    QFile file(newName);
    if (file.exists()) {
        return file.remove() && QFile::copy(fileName, newName);
    } else {
        return QFile::copy(fileName, newName);
    }
}

bool CombineFile(const QString &fileName1, const QString &fileName2, const QString &newName) {
    QFile file1(fileName1);
    QFile file2(fileName2);
    QFile file3(newName);

    if (file1.open(QIODevice::ReadOnly) && file2.open(QIODevice::ReadOnly) &&
        file3.open(QIODevice::WriteOnly)) {
    } else {
        return false;
    }

    QByteArray bytes1, bytes2;
    bytes1 = file1.readAll();
    bytes2 = file2.readAll();

    file3.write(bytes1 + bytes2);

    file1.close();
    file2.close();
    file3.close();

    return true;
}

void RevealFile(const QString &filename) {
    QFileInfo info(filename);
#if defined(Q_OS_WINDOWS)
    if (info.isFile()) {
        QStringList cmds;
        cmds << "/e,"
             << "/select," << QDir::toNativeSeparators(filename);
        QProcess::startDetached("explorer.exe", cmds);
    } else if (info.isDir()) {
        QStringList cmds;
        cmds << "/e,"
             << "/root," << QDir::toNativeSeparators(filename);
        QProcess::startDetached("explorer.exe", cmds);
    }
#elif defined(Q_OS_MAC)
    if (info.isDir()) {
        if (!filename.endsWith(Slash)) {
            filename.append(Slash);
        }
        QProcess::startDetached("bash", {"-c", "open \'" + filename + "\'"});
    } else if (info.isFile()) {
        QStringList scriptArgs;
        scriptArgs << QLatin1String("-e")
                   << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
                          .arg(filename);
        QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
        scriptArgs.clear();
        scriptArgs << QLatin1String("-e")
                   << QLatin1String("tell application \"Finder\" to activate");
        QProcess::execute("/usr/bin/osascript", scriptArgs);
    }
#else
    if (info.isDir()) {
        QProcess::startDetached("bash", {"-c", "xdg-open \'" + filename + "\'"});
    } else if (info.isFile()) {
        QString arg = PathFindUpper(filename);
        QProcess::startDetached("bash", {"-c", "xdg-open \'" + arg + "\'"});
    }
#endif
}
