#include "ParamsDialArea.h"
#include "../../Graphics/GraphicsLifter.h"
#include "../../TuningGroup.h"
#include "../ParamsInterface.h"

ParamsDialArea::ParamsDialArea(ParamsInterface *editor, QWidget *parent) : QWidget(parent) {
    m_ptrs = editor->ptrs();

    m_textColor = Qt::black;
}

ParamsDialArea::~ParamsDialArea() {
}

void ParamsDialArea::setScale(Qs::Panels::Params params) {
    switch (params) {
    case Qs::Panels::Intensity:
        highest = 200;
        middle = 100;
        lowest = 0;
        break;
    case Qs::Panels::Modulation:
        highest = 200;
        middle = 0;
        lowest = -200;
        break;
    case Qs::Panels::Velocity:
        highest = 200;
        middle = 100;
        lowest = -100;
        break;
    default:
        break;
    }
    update();
}

QColor ParamsDialArea::textColor() const {
    return m_textColor;
}

void ParamsDialArea::setTextColor(const QColor &textColor) {
    m_textColor = textColor;

    update();
    emit colorChanged();
}

TuningGroup *ParamsDialArea::ptrs() const {
    return m_ptrs;
}

void ParamsDialArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setClipRegion(event->region());
    painter.setRenderHint(QPainter::Antialiasing);

    double retract = 5;
    QRect entityRect(retract, GraphicsLifter::Radius, width() - 2 * retract,
                     height() - 2 * GraphicsLifter::Radius);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(m_textColor);

    painter.drawText(entityRect, Qt::AlignTop | Qt::AlignRight, QString::number(highest));
    painter.drawText(entityRect, Qt::AlignVCenter | Qt::AlignRight, QString::number(middle));
    painter.drawText(entityRect, Qt::AlignBottom | Qt::AlignRight, QString::number(lowest));
}
