#include "QUtils.h"

QFont mainFont(int pixelSize, int weight, bool italic) {
    QFont font;
    font.setStyleStrategy(QFont::PreferAntialias);

    font.setFamily(AppFontName);
    font.setPixelSize(pixelSize);
    font.setWeight(weight);
    font.setItalic(italic);
    return font;
}

QFont uiFont() {
    return mainFont(12);
}

QString PathFindFileName(QString s) {
    QFileInfo file(s);
    return file.fileName();
}

QString PathFindFileName(QString s, QString folder) {
    s = QDir::fromNativeSeparators(s);
    folder = QDir::fromNativeSeparators(folder);

    if (folder.rightRef(1) != Slash) {
        folder += Slash;
    }
    if (s.size() <= folder.size() || !s.startsWith(folder)) {
        return s;
    } else {
        return s.mid(folder.size());
    }
}

QString PathFindUpper(QString s) {
    QFileInfo file(s);
    return file.absolutePath();
}

QString PathFindNextLevel(QString s, QString folder) {
    if (!s.startsWith(folder)) {
        return "";
    }
    QString suffix = s.mid(folder.size());
    if (suffix.startsWith(Slash)) {
        suffix = suffix.mid(1);
    }
    int slashIndex = suffix.indexOf(Slash);
    if (slashIndex < 0) {
        return suffix;
    }
    return suffix.mid(0, slashIndex);
}

QString PathFindSuffix(QString s) {
    QFileInfo file(s);
    return file.suffix();
}

bool isPathRelative(QString fullPath) {
    QFileInfo fileInfo(fullPath);
    return !fullPath.isEmpty() && fileInfo.isRelative();
}

bool isDirExist(QString fullPath) {
    QFileInfo fileInfo(fullPath);
    return !fullPath.isEmpty() && fileInfo.isDir();
}

bool isFileExist(QString fullFileName) {
    QFileInfo fileInfo(fullFileName);

    return !fullFileName.isEmpty() && fileInfo.isFile();
}

void CreateDir(QString fullPath) {
    QDir dir(fullPath);

    if (dir.exists()) {
        return;
    } else {
        dir.mkpath(fullPath);
    }
}

void DestroyDir(QString fullPath) {
    QDir dir(fullPath);
    if (!fullPath.isEmpty() && dir.exists()) {
        dir.removeRecursively();
    }
}

bool isSameFile(QString filename1, QString filename2) {
    QFileInfo fileInfo1(filename1), fileInfo2(filename2);

    QString s1 = fileInfo1.canonicalFilePath();
    QString s2 = fileInfo2.canonicalFilePath();

    return !(s1.isEmpty() || s2.isEmpty()) && s1 == s2;
}

bool isSubDir(QString dirname, QString subdirname) {
    QFileInfo dir(dirname), subdir(subdirname);

    if (dir.isDir() && (subdir.exists())) {
        QString dirpath = dir.absoluteFilePath();
        QString subdirpath = subdir.absoluteFilePath();
        if (dirpath != subdirpath && subdirpath.startsWith(dirpath)) {
            return true;
        }
    }
    return false;
}

bool CombineFile(QString oFile1, QString oFile2, QString oFile3) {
    QFile aFile1(oFile1);
    QFile aFile2(oFile2);
    QFile aFile3(oFile3);

    if (aFile1.open(QIODevice::ReadOnly) && aFile2.open(QIODevice::ReadOnly) &&
        aFile3.open(QIODevice::WriteOnly)) {

    } else {
        return 0;
    }

    QByteArray bytes1, bytes2;
    bytes1 = aFile1.readAll();
    bytes2 = aFile2.readAll();

    aFile3.write(bytes1 + bytes2);

    aFile1.close();
    aFile2.close();
    aFile3.close();

    return 1;
}

bool RemoveFile(QString fileName) {
    QFileInfo FileInfo(fileName);

    if (FileInfo.isFile()) {
        return QFile::remove(fileName);
    }
    return false;
}


bool CopyFile(QString fileName, QString newName) {
    if (isFileExist(newName)) {
        return RemoveFile(newName) && QFile::copy(fileName, newName);
    } else {
        return QFile::copy(fileName, newName);
    }
}

void RemoveFilesWithPrefix(QString strDir, QString prefix) {
    if (!isDirExist(strDir)) {
        return;
    }

    QDir dir;
    QFileInfoList fileList;
    QFileInfo curFile;

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    dir.setPath(strDir);
    fileList = dir.entryInfoList();

    for (int i = fileList.size() - 1; i >= 0; i--) {
        curFile = fileList[i];
        if (prefix.isEmpty() || curFile.fileName().startsWith(prefix)) {
            QFile fileTemp(curFile.filePath());
            fileTemp.remove();
        }
    }
}

QDateTime GetFileLastModifyTime(QString filename) {
    QFileInfo file(filename);

    if (!file.isFile()) {
        return QDateTime();
    }

    return file.lastModified();
}

bool isNumber(QString s, bool considerDot, bool considerNeg) {
    bool flag = true;

    for (QString::size_type i = 0; i < s.size(); ++i) {
        if ((s[i] >= '0' && s[i] <= '9') || (considerDot && s[i] == '.') ||
            (considerNeg && s[i] == '-')) {
            // is Number
        } else {
            flag = false;
            break;
        }
    }

    return flag;
}

QList<int> toIntList(const QStringList &list) {
    QList<int> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        bool isNum;
        int num = it->toInt(&isNum);
        if (!isNum) {
            return {};
        }
        res.append(num);
    }
    return res;
}

QList<double> toDoubleList(const QStringList &list) {
    QList<double> res;
    for (auto it = list.begin(); it != list.end(); ++it) {
        bool isNum;
        int num = it->toDouble(&isNum);
        if (!isNum) {
            return {};
        }
        res.append(num);
    }
    return res;
}

bool equalDouble(double a, double b) {
    return QString::number(a) == QString::number(b);
}

QString removeTailSlashes(const QString &dirname) {
    QString path = dirname;
    while (!path.isEmpty() && (path.endsWith('/') || path.endsWith('\\'))) {
        path = path.mid(0, path.size() - 1);
    }
    return path;
}

void RevealFile(QString filename) {
#if defined(Q_OS_WINDOWS)
    if (isFileExist(filename)) {
        QStringList cmds;
        cmds << "/e,"
             << "/select," << QDir::toNativeSeparators(filename);
        QProcess::startDetached("explorer.exe", cmds);
    } else if (isDirExist(filename)) {
        QStringList cmds;
        cmds << "/e,"
             << "/root," << QDir::toNativeSeparators(filename);
        QProcess::startDetached("explorer.exe", cmds);
    }
#elif defined(Q_OS_MAC)
    if (isDirExist(filename)) {
        if (!filename.endsWith(Slash)) {
            filename.append(Slash);
        }
        QProcess::startDetached("bash", {"-c", "open \'" + filename + "\'"});
    } else if (isFileExist(filename)) {
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
    if (isDirExist(filename)) {
        QProcess::startDetached("bash", {"-c", "xdg-open \'" + filename + "\'"});
    } else if (isFileExist(filename)) {
        QString arg = PathFindUpper(filename);
        QProcess::startDetached("bash", {"-c", "xdg-open \'" + arg + "\'"});
    }
#endif
}
