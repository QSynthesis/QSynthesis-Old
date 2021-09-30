#ifndef QUTILS_H
#define QUTILS_H

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QProcess>

#include "Macros.h"
#include "Types.h"
#include "Variables.h"

class MainWindow;

// Global Constants
const QRect NO_RECT = QRect(0, 0, 0, 0);
const QRectF NO_RECTF = QRectF(0, 0, 0, 0);

const QString CLIPBOARD_FORMAT_NAME_NOTE = "qsynthesis/notes";

// Global Functions
QFont mainFont(int pixelSize = 15, int weight = QFont::Normal, bool italic = false);

QFont uiFont();

QString PathFindFileName(QString s);

QString PathFindFileName(QString s, QString folder);

QString PathFindSuffix(QString s);

QString PathFindUpper(QString s);

QString PathFindNextLevel(QString s, QString folder);

bool isPathRelative(QString fullPath); // If path is a relative path

bool isDirExist(QString fullPath); // If the folder exists

bool isFileExist(QString fullFileName); // If the file exists

void CreateDir(QString fullPath); // Make a directory

void DestroyDir(QString fullPath); // Remove a directory

bool isSameFile(QString filename1, QString filename2);

bool isSubDir(QString dirname, QString subdirname);

bool CombineFile(QString oFile1, QString oFile2, QString oFile3);

bool RemoveFile(QString fileName);

bool CopyFile(QString fileName, QString newName);

void RemoveFilesWithPrefix(QString strDir, QString prefix);

QDateTime GetFileLastModifyTime(QString filename);

bool isNumber(QString s, bool considerDot, bool considerNeg);

QList<int> toIntList(const QStringList &list);

QList<double> toDoubleList(const QStringList &list);

bool equalDouble(double a, double b);

void RevealFile(QString filename);

#endif // QUTILS_H
