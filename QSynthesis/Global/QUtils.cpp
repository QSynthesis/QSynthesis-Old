#include "QUtils.h"

QFont mainFont(int pixelSize, int weight, bool italic) {
    QFont font;
    font.setStyleStrategy(QFont::PreferAntialias);

    font.setFamily(AppFontName);
    font.setPixelSize(pixelSize);
    font.setWeight(weight);
    font.setItalic(italic);
    return font;
}

QFont uiFont() {
    return mainFont(12);
}

QString PathFindFileName(QString s) {
    QFileInfo file(s);
    return file.fileName();
}

QString PathFindFileName(QString s, QString folder) {
    s = QDir::fromNativeSeparators(s);
    folder = QDir::fromNativeSeparators(folder);

    if (folder.rightRef(1) != Slash) {
        folder += Slash;
    }
    if (s.size() <= folder.size() || !s.startsWith(folder)) {
        return s;
    } else {
        return s.mid(folder.size());
    }
}

QString PathFindUpper(QString s) {
    QFileInfo file(s);
    return file.absolutePath();
}

QString PathFindNextLevel(QString s, QString folder) {
    if (!s.startsWith(folder)) {
        return "";
    }
    QString suffix = s.mid(folder.size());
    if (suffix.startsWith(Slash)) {
        suffix = suffix.mid(1);
    }
    int slashIndex = suffix.indexOf(Slash);
    if (slashIndex < 0) {
        return suffix;
    }
    return suffix.mid(0, slashIndex);
}

QString PathFindSuffix(QString s) {
    QFileInfo file(s);
    return file.suffix();
}

bool equalDouble(double a, double b) {
    return QString::number(a) == QString::number(b);
}
