#ifndef METHODS_H
#define METHODS_H

#include <QDomElement>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QSvgRenderer>
#include <QWidget>

#include "QUtils.h"

MainWindow *Root(QWidget *w);

QColor invertedColor(const QColor &crColor);

QPixmap createBitmapFromSVG(QString fullpath, QSize size);

QByteArray fromSvgFileAndSetColor(QString fullpath, QColor color);

QPixmap createBitmapFromSVG_W(QString fullpath, QSize size, QColor c);

void setWidgetBackColor(QWidget *w, QColor c = Qt::transparent);

void pathCosineTo(QPainterPath &path, QPointF prev, QPointF curr);

void pathCosineJTo(QPainterPath &path, QPointF prev, QPointF curr);

void pathCosineRTo(QPainterPath &path, QPointF prev, QPointF curr);

double Hypotenuse(double x1, double x2, double y1, double y2);

bool loadStyleFromResource(QWidget *w, const QString &filebody);

#endif // METHODS_H
