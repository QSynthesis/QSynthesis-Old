#include "ColorTheme.h"
#include "application.h"
#include "mainwindow.h"

ColorTheme::ColorTheme() {
}

ColorTheme::~ColorTheme() {
}

void ColorTheme::loadTheme(int index) {
    QFile qss;
#ifdef Q_OS_MAC
    if (index == 0) {
        qss.setFileName(":/themes/theme-mac.qss");
    } else if (index == 1) {
        qss.setFileName(":/themes/theme-mac-dark.qss");
    }
#else
    if (index == 0) {
        qss.setFileName(":/themes/theme-win.qss");
    } else if (index == 1) {
        qss.setFileName(":/themes/theme-win-dark.qss");
    }
#endif

    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qRoot->setStyleSheet(qss.readAll());
        qss.close();
    }
}
