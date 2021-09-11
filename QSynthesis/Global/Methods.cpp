#include "Methods.h"
#include "mainwindow.h"

#include <cmath>

MainWindow *Root(QWidget *w) {
    return qobject_cast<MainWindow *>(w->window());
}

QColor invertedColor(const QColor &crColor) {
    QColor crInvert = crColor;
    crInvert.setRgb(255 - crInvert.red(), 255 - crInvert.green(), 255 - crInvert.blue());
    return crInvert;
}

QPixmap createBitmapFromSVG(QString fullpath, QSize size) {
    QSvgRenderer svgRender(fullpath);
    QPixmap bmp(size);
    bmp.fill(Qt::transparent); // Set background transparent
    QPainter painter(&bmp);
    painter.setRenderHint(QPainter::Antialiasing);
    svgRender.render(&painter);
    return bmp;
}

QByteArray fromSvgFileAndSetColor(QString fullpath, QColor color) {
    QFile file(fullpath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    QString colorStr = color.name(QColor::HexRgb).mid(1);

    for (int k = 0; k < data.size(); ++k) {
        if (data.at(k) == '#') {
            int i = k + 1;
            bool isColor = true;
            for (int j = i; j < qMin(data.size(), i + colorStr.size()); ++j) {
                QChar ch = data.at(j);
                if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') ||
                    (ch >= 'a' && ch <= 'f')) {
                } else {
                    isColor = false;
                    break;
                }
            }
            if (isColor) {
                for (int j = i; j < i + colorStr.size(); ++j) {
                    data[j] = colorStr[j - i].toLatin1();
                }
            }
        }
    }

    return data;
}

QPixmap createBitmapFromSVG_W(QString fullpath, QSize size, QColor c) {
    QSvgRenderer svgRender(fromSvgFileAndSetColor(fullpath, c));
    QPixmap bmp(size);
    bmp.fill(Qt::transparent); // Set background transparent
    QPainter painter(&bmp);
    painter.setRenderHint(QPainter::Antialiasing);
    svgRender.render(&painter);
    return bmp;
}

void setWidgetBackColor(QWidget *w, QColor c) {
    QPalette palette;
    palette.setColor(QPalette::Background, c);
    w->setAutoFillBackground(true);
    w->setPalette(palette);
}

void pathCosineTo(QPainterPath &path, QPointF prev, QPointF curr) {
    double ratio = 0.364212423249; // Coefficient of bessel and sine

    QPointF assist1 = QPointF(prev.x() * (1 - ratio) + curr.x() * ratio, prev.y());
    QPointF assist2 = QPointF(prev.x() * ratio + curr.x() * (1 - ratio), curr.y());

    path.cubicTo(assist1, assist2, curr);
}

void pathCosineJTo(QPainterPath &path, QPointF prev, QPointF curr) {
    double ratioX = 342.0 / 942.0;

    double ratioA = 305.0 / 942.0;
    double ratioB = 305.0 / 600.0;

    QPointF assist1 = QPointF(prev.x() * (1 - ratioX) + curr.x() * ratioX, prev.y());

    QPointF assist2 = QPointF(prev.x() * ratioA + curr.x() * (1 - ratioA),
                              prev.y() * ratioB + curr.y() * (1 - ratioB));

    path.cubicTo(assist1, assist2, curr);
}

void pathCosineRTo(QPainterPath &path, QPointF prev, QPointF curr) {

    double ratioX = 342.0 / 942.0;

    double ratioA = 305.0 / 942.0;
    double ratioB = 305.0 / 600.0;

    QPointF assist1 = QPointF(curr.x() * ratioA + prev.x() * (1 - ratioA),
                              curr.y() * ratioB + prev.y() * (1 - ratioB));

    QPointF assist2 = QPointF(curr.x() * (1 - ratioX) + prev.x() * ratioX, curr.y());

    path.cubicTo(assist1, assist2, curr);
}

double Hypotenuse(double x1, double x2, double y1, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool loadStyleFromResource(QWidget *w, const QString &filebody) {
    QFile qss;
    qss.setFileName(":/themes/" + filebody + ".qss");
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        w->setStyleSheet(qss.readAll());
        qss.close();
        return true;
    }
    return false;
}
