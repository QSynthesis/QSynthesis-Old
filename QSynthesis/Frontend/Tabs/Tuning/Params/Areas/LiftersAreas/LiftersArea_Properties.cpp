#include "../LiftersArea.h"

QColor LiftersArea::backColor() const {
    return m_backColor;
}

void LiftersArea::setBackColor(const QColor &backColor) {
    m_backColor = backColor;
}

QColor LiftersArea::sectionLineColor() const {
    return m_sectionLineColor;
}

void LiftersArea::setSectionLineColor(const QColor &sectionLineColor) {
    m_sectionLineColor = sectionLineColor;
}

QColor LiftersArea::timeLineColor() const {
    return m_timeLineColor;
}

void LiftersArea::setTimeLineColor(const QColor &timeLineColor) {
    m_timeLineColor = timeLineColor;
}
