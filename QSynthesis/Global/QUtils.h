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

#include "Constants.h"
#include "Macros.h"
#include "Primary.h"
#include "SystemApis.h"
#include "Types.h"
#include "Variables.h"

class MainWindow;

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

bool RemoveFile(QString fileName);

int RemoveFilesWithPrefix(QString strDir, QString prefix);

int RemoveFilesWithPrefixNumber(QString strDir, int prefix);

QDateTime GetFileLastModifyTime(QString filename);

bool isNumber(QString s, bool considerDot, bool considerNeg);

bool equalDouble(double a, double b);

#endif // QUTILS_H
