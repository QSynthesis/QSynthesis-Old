#include "TransparentContainer.h"

#include <QBrush>
#include <QPainter>

TransparentContainer::TransparentContainer(QWidget *parent) : QFrame(parent) {
    setAttribute(Qt::WA_StyledBackground);
    m_wallpaper = Qt::transparent;
}

QColor TransparentContainer::wallpaper() const {
    return m_wallpaper;
}

void TransparentContainer::setWallpaper(const QColor &wallpaper) {
    m_wallpaper = wallpaper;
    emit wallpaperChanged();

    update();
}

void TransparentContainer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(m_wallpaper);
    painter.setPen(Qt::NoPen);

    QRect rect = contentsRect();
    painter.drawRect(rect);
}
