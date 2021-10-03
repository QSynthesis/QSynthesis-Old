#ifndef TOTAL_H
#define TOTAL_H

#include "Managers/DataManager.h"
#include "mainwindow.h"

#include <QFontDatabase>
#include <QTextCodec>

void initLocale();

void initSingletons();

void initFonts();

void removeSingletons();

void created();

void destroyed();

#endif // TOTAL_H
