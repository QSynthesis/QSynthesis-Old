#include "SectionsLine.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>

SectionsLine::SectionsLine(QWidget *parent) : QWidget(parent) {
    m_lineColor = Qt::lightGray;
    m_numColor = Qt::black;
    m_beatColor = Qt::black;

    setCount(0);
    setBeat(4, 4);
}

SectionsLine::~SectionsLine() {
}

void SectionsLine::adjustWidth() {
}

int SectionsLine::count() const {
    return m_count;
}

void SectionsLine::setCount(int count) {
    m_count = count;
    update();
}

QPoint SectionsLine::beat() const {
    return m_beat;
}

void SectionsLine::setBeat(const QPoint &beat) {
    m_beat = beat;
    update();
}

void SectionsLine::setBeat(int num, int den) {
    setBeat(QPoint(num, den));
}

QColor SectionsLine::lineColor() const {
    return m_lineColor;
}

void SectionsLine::setLineColor(const QColor &lineColor) {
    m_lineColor = lineColor;
    update();
    emit colorChanged();
}

QColor SectionsLine::numColor() const {
    return m_numColor;
}

void SectionsLine::setNumColor(const QColor &numColor) {
    m_numColor = numColor;
    update();
    emit colorChanged();
}

QColor SectionsLine::beatColor() const {
    return m_beatColor;
}

void SectionsLine::setBeatColor(const QColor &beatColor) {
    m_beatColor = beatColor;
    update();
    emit colorChanged();
}

int SectionsLine::sectionWidth() const {
    return m_width;
}

void SectionsLine::setSectionWidth(int width) {
    m_width = width;
}

void SectionsLine::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setClipRegion(event->region());
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(m_lineColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(m_numColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QRect rect = this->rect();

    int i, j, k;
    int retract = 5;

    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawLine(QPoint(rect.left(), rect.bottom()),
                     QPoint(rect.right(), rect.bottom()));

    int curX;

    int maxSemiquavers = m_count * 16;
    int unit = 16 / m_beat.y();

    double unitX = m_width * 4 / unit;

    QRectF rectTop, rectHalfTop, rectText;

    rectTop.setTop(0);
    rectTop.setBottom(rect.bottom());

    rectHalfTop.setTop(rectTop.center().y());
    rectHalfTop.setBottom(rectTop.bottom());

    rectText = rectTop;

    j = 0;
    k = 0;
    for (i = unit; i <= maxSemiquavers; i += unit) {
        curX = j * unitX;

        if (j % m_beat.x() == 0) {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectTop.top()), QPointF(curX, rectTop.bottom()));

            rectText.setLeft(curX);
            rectText.setWidth(unitX * m_beat.x());
            rectText.adjust(retract, 0, -retract, 0);
            painter.setPen(pen2);
            painter.drawText(rectText, Qt::AlignVCenter | Qt::AlignLeft, QString::number(k));
            k++;
        } else {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectHalfTop.top()), QPointF(curX, rectHalfTop.bottom()));
        }
        j++;
    }
}
