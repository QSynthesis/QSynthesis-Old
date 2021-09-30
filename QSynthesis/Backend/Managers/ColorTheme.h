#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <QFile>

#include "Macros.h"

class ColorTheme {
    Q_SINGLETON(ColorTheme)
public:
    ColorTheme();
    ~ColorTheme();

    static void loadTheme(int index);
};

#endif // COLORTHEME_H
