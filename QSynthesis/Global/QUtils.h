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

bool equalDouble(double a, double b);

#endif // QUTILS_H
