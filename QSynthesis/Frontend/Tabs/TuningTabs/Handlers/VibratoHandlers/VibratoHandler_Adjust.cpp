#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/VibratoHandles/VibratoLineHandle.h"
#include "../../Graphics/VibratoHandles/VibratoPlaneHandle.h"
#include "../Mode2Handler.h"

void Mode2Handler::updateVibratoLength() {
    updateOthersBySide();

    // --- 临时变化
    Vibrato[0] = (1 - btnSide->value().x()) * 100.0;

    update();
}

void Mode2Handler::updateVibratoGraph() {
    // 重新绘制图像
    if (btnFrequency->isMoving()) {
        updatePhaseByFrequency();
        btnPhase->setValueX(Vibrato[5] / 100.0);

        // --- 临时变化
        Vibrato[1] = btnFrequency->value().x() * (maxPeriod - minPeriod) + minPeriod;
    } else if (btnPhase->isMoving()) {
        // --- 临时变化
        Vibrato[5] = btnPhase->value().x() * 100.0;
    }
    update();
}

void Mode2Handler::updateVibratoHeight() {
    if (btnTop->isMoving()) {
        btnBottom->setPosition(btnCenter->position() +
                               qAbs(btnCenter->position() - btnTop->position()));
    } else {
        btnTop->setPosition(btnCenter->position() -
                            qAbs(btnCenter->position() - btnBottom->position()));
    }

    updateEaseByHeight();

    // --- 临时变化
    double dy = -double(btnTop->position() - btnCenter->position()) / m_note->height() * 100.0;
    if (dy == 0) {
        dy = 1;
    }
    Vibrato[2] = dy;
    // 峰谷修改后高度也会跟着变化
    Vibrato[6] = -double(btnCenter->position() - m_note->headPos().y()) / m_note->height() /
                 (Vibrato[2] / 100.0) * 100.0;
    // --- 临时变化

    update();
}

void Mode2Handler::updateVibratoEase() {
    updateHeightByEase();
    restrictHeightByOffset();

    // --- 临时变化
    if (btnEaseIn->isMoving()) {
        Vibrato[3] = btnEaseIn->value() * 100.0;
    } else if (btnEaseOut->isMoving()) {
        Vibrato[4] = (1 - btnEaseOut->value()) * 100.0;
    }
    // --- 临时变化

    update();
}

void Mode2Handler::updateVibratoOffset() {
    relieveHeightByOffset();
    updateOthersByOffset();

    // --- 临时变化
    Vibrato[6] = -double(btnCenter->position() - m_note->headPos().y()) / m_note->height() /
                 (Vibrato[2] / 100.0) * 100.0;

    // --- 临时变化

    update();
}

void Mode2Handler::saveMovingVibrato() {
    if (btnCenter->isMoving()) {
        restrictHeightByOffset();
    }

    // 原来长度是0 现在长度也是0 没有保存的意义
    if (m_note->Note.vibrato[0] == 0 && Vibrato[0] == 0) {
        qDebug() << "Length = 0 , abandon.";
        Vibrato = m_note->Note.vibrato;
        update();
        return;
    } else {
        qDebug() << "Save Vibrato";
    }

    m_editor->afterModifyVibrato(m_note);
}
