#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <QFile>

class ColorTheme {
public:
    ColorTheme();
    ~ColorTheme();

    static void loadTheme(int index);
};

#endif // COLORTHEME_H
