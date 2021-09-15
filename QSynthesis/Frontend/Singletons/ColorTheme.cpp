#include "ColorTheme.h"

Q_SINGLETON_DECLARE(ColorTheme)

ColorTheme::ColorTheme() {
}

ColorTheme::~ColorTheme() {
}

void ColorTheme::previewTheme(int index) {
    qDebug() << "Preview:" << index;
}
