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

int RemoveFilesWithPrefix(QString strDir, QString prefix) {
    if (!isDirExist(strDir)) {
        return 0;
    }

    QDir dir;
    QFileInfoList fileList;
    QFileInfo curFile;
    int cnt = 0;

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    dir.setPath(strDir);
    fileList = dir.entryInfoList();

    for (int i = fileList.size() - 1; i >= 0; i--) {
        curFile = fileList[i];
        if (prefix.isEmpty() || curFile.fileName().startsWith(prefix)) {
            QFile fileTemp(curFile.filePath());
            if (fileTemp.remove()) {
                cnt++;
            }
        }
    }
    return cnt;
}

int RemoveFilesWithPrefixNumber(QString strDir, int prefix) {
    if (!isDirExist(strDir)) {
        return 0;
    }

    QDir dir;
    QFileInfoList fileList;
    QFileInfo curFile;
    int cnt = 0;

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    dir.setPath(strDir);
    fileList = dir.entryInfoList();

    for (int i = fileList.size() - 1; i >= 0; i--) {
        curFile = fileList[i];
        QString num = QString::number(prefix);
        QString filename = curFile.fileName();
        if (filename.startsWith(num) &&
            (filename.size() == num.size() || !filename.at(num.size()).isNumber())) {
            QFile fileTemp(curFile.filePath());
            if (fileTemp.remove()) {
                cnt++;
            }
        }
    }
    return cnt;
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

bool equalDouble(double a, double b) {
    return QString::number(a) == QString::number(b);
}
