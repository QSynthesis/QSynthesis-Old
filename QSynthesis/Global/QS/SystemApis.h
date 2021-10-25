#ifndef SYSTEMAPIS_H
#define SYSTEMAPIS_H

#include <QString>
#include <QTextCodec>

QTextCodec *GetUtfCodec(const QByteArray &data);

QStringList FindRecursiveDirs(const QString &base);

bool CopyFile(const QString &fileName, const QString &newName);

bool CombineFile(const QString &fileName1, const QString &fileName2, const QString &newName);

void RevealFile(const QString &filename);

#endif // SYSTEMAPIS_H
