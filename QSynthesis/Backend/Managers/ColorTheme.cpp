#include "ColorTheme.h"
#include "application.h"

Q_SINGLETON_DECLARE(ColorTheme)

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
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
}
