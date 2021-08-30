#include "../../../TuningGroup.h"
#include "../LiftersArea.h"

void LiftersArea::adjustWidth() {
    setSceneRect(QRectF(0, 0, m_ptrs->currentWidth * 4 * (m_ptrs->currentSections + 1), height()));
    // Call scene rect change handler
}

void LiftersArea::updateBackground() {
    int curWidth = m_ptrs->currentWidth;

    double lineWidth = 1;

    // Draw Background Unit
    double totalWidth = curWidth * 4;
    double totalHeight = m_standardHeight;

    if (totalWidth == 0 || totalHeight == 0) {
        return;
    }

    QPixmap pixmap(totalWidth, totalHeight);
    pixmap.fill(m_backColor);

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);

    for (int i = 1; i <= 3; ++i) {
        painter.setBrush(m_timeLineColor);
        painter.drawRect(QRectF(curWidth * i - lineWidth / 2, 0, lineWidth, totalHeight));
    }

    painter.setBrush(m_sectionLineColor);
    painter.drawRect(QRectF(0, 0, lineWidth / 2, totalHeight));
    painter.drawRect(QRectF(totalWidth - lineWidth / 2, 0, lineWidth / 2, totalHeight));

    setBackgroundBrush(pixmap);
}
