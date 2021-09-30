#ifndef TOTAL_H
#define TOTAL_H

#include "Singletons/AppAssistant.h"
#include "mainwindow.h"

#include <QTextCodec>
#include <QFontDatabase>

void initLocale();

void initSingletons();

void initFonts();

void removeSingletons();

void created();

void destroyed();

#endif // TOTAL_H
