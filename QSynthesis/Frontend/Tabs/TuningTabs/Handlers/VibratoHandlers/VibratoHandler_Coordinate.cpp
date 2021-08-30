#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/VibratoHandles/VibratoLineHandle.h"
#include "../../Graphics/VibratoHandles/VibratoPlaneHandle.h"
#include "../Mode2Handler.h"

void Mode2Handler::updateFrequencyBySide() {
    QRectF frqRect;

    double x0 = btnSide->pos().x();
    double len = m_note->x() + m_note->width() - x0;
    double x1 = x0 + len * minPeriod / maxPeriod;

    frqRect.setTopLeft(QPointF(x1, btnFrequency->pos().y()));
    frqRect.setBottomRight(
        QPointF(m_note->staticPos().x() + m_note->width(), btnFrequency->pos().y()));
    btnFrequency->setRegion(frqRect);
}

void Mode2Handler::updatePhaseByFrequency() {
    QRect phaseRect;

    phaseRect.setTopLeft(QPoint(btnSide->pos().x(), btnPhase->pos().y()));
    phaseRect.setBottomRight(QPoint(btnFrequency->pos().x(), btnPhase->pos().y()));
    btnPhase->setRegion(phaseRect);
}

void Mode2Handler::updateOthersBySide() {
    // 根据边界调整另外两个点按钮
    // 根据颤音信息调整两个点按钮坐标
    updateFrequencyBySide();
    btnFrequency->setValueX((Vibrato[1] - minPeriod) / (maxPeriod - minPeriod));

    updatePhaseByFrequency();
    btnPhase->setValueX(Vibrato[5] / 100.0);

    // 调整峰谷与中心
    updateHeightBySide();

    // 根据颤音信息调整上下深度的纵坐标
    btnCenter->setPosition(m_note->bodyPos().y() -
                           Vibrato[6] / 100.0 * Vibrato[2] / 100.0 * m_note->height());

    btnTop->setPosition(btnCenter->position() - Vibrato[2] / 100.0 * m_note->height());
    btnBottom->setPosition(btnCenter->position() + Vibrato[2] / 100.0 * m_note->height());

    // 根据峰谷调整淡入淡出
    updateEaseByHeight();

    // 根据颤音信息调整淡入淡出的横坐标
    btnEaseIn->setValue(Vibrato[3] / 100.0);
    btnEaseOut->setValue(1 - Vibrato[4] / 100.0);

    // 根据淡入淡出横坐标重新调整上下深度
    updateHeightByEase();

    // 重新限制上下深度的纵坐标
    restrictHeightByOffset();
}

void Mode2Handler::updateHeightBySide() {
    QRectF verticalRect;

    verticalRect.setTopLeft(QPointF(btnSide->pos().x(), m_geometry.top()));
    verticalRect.setBottomRight(QPointF(m_note->tailPos().x(), m_geometry.bottom()));

    btnCenter->setRegion(verticalRect);
    btnTop->setRegion(verticalRect);
    btnBottom->setRegion(verticalRect);
}

void Mode2Handler::updateEaseByHeight() {
    QRectF horizontalRect;

    horizontalRect.setTopLeft(QPoint(btnSide->pos().x(), btnTop->position()));
    horizontalRect.setBottomRight(QPoint(m_note->tailPos().x(), btnBottom->position()));

    btnEaseIn->setRegion(horizontalRect);
    btnEaseOut->setRegion(horizontalRect);
}

void Mode2Handler::updateHeightByEase() {
    QRectF verticalRect;

    int btnLeftPos = qMin(btnEaseIn->position(), btnEaseOut->position());
    int btnRightPos = qMax(btnEaseIn->position(), btnEaseOut->position());

    verticalRect.setTopLeft(QPoint(btnLeftPos, m_geometry.top()));
    verticalRect.setBottomRight(QPoint(btnRightPos, m_geometry.bottom()));

    btnCenter->setRegion(verticalRect);
    btnTop->setRegion(verticalRect);
    btnBottom->setRegion(verticalRect);
}

void Mode2Handler::updateOthersByOffset() {
    double dis = qAbs(btnTop->position() - btnBottom->position());

    btnTop->setPosition(btnCenter->position() - dis / 2);
    btnBottom->setPosition(btnCenter->position() + dis / 2);

    updateEaseByHeight();
}

void Mode2Handler::restrictHeightByOffset() {
    QRectF verticalRect2;

    verticalRect2 = btnCenter->region();
    verticalRect2.setBottom(btnCenter->position());

    btnTop->setRegion(verticalRect2);

    verticalRect2 = btnCenter->region();
    verticalRect2.setTop(btnCenter->position());

    btnBottom->setRegion(verticalRect2);
}

void Mode2Handler::relieveHeightByOffset() {
    QRectF verticalRect2;

    verticalRect2 = btnCenter->region();

    btnTop->setRegion(verticalRect2);
    btnBottom->setRegion(verticalRect2);
}
