#ifndef SYSTEMAPIS_H
#define SYSTEMAPIS_H

#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QTextCodec>

#define isPathRelative(s) QDir::isRelativePath(s)
#define isPathExist(s) (!isPathRelative(s) && QFileInfo(s).exists())
#define isFileExist(s) (!isPathRelative(s) && QFileInfo(s).isFile())
#define isDirExist(s) (!isPathRelative(s) && QFileInfo(s).isDir())
#define isSamePath(A, B) (QFileInfo(A).canonicalFilePath() == QFileInfo(B).canonicalFilePath())
#define CreateDir(s) (QDir(s).mkpath(s))
#define DestroyDir(s) (isDirExist(s) && QDir(s).removeRecursively())
#define RemoveFile(s) QFile::remove(s)

QTextCodec *GetUtfCodec(const QByteArray &data);

QStringList FindRecursiveDirs(const QString &base);

bool CopyFile(const QString &fileName, const QString &newName);

bool CombineFile(const QString &fileName1, const QString &fileName2, const QString &newName);

int RemoveFilesWithPrefixString(const QString &strDir, const QString &prefix);

int RemoveFilesWithPrefixNumber(const QString &strDir, int prefix);

void RevealFile(const QString &filename);

#endif // SYSTEMAPIS_H
