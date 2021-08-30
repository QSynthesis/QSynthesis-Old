#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/VibratoHandles/VibratoLineHandle.h"
#include "../../Graphics/VibratoHandles/VibratoPlaneHandle.h"
#include "../Mode2Handler.h"

const double Mode2Handler::minPeriod = 32;
const double Mode2Handler::maxPeriod = 512;

Mode2Handler *Mode2Handler::VBREditorHolder = nullptr;

void Mode2Handler::fromNoteVibrato() {
    replaceVibrato(m_note->Note.vibrato);
}

void Mode2Handler::toNoteVibrato() {
    m_note->Note.vibrato = Vibrato;
}

void Mode2Handler::replaceVibrato(const QList<double> &vbr) {
    if (vbr.size() < 8) {
        Vibrato.clear();
        removeVibrtoEditor();
    } else {
        Vibrato = vbr;
    }
}

void Mode2Handler::clearVibrato() {
    replaceVibrato({});
}

void Mode2Handler::makeDefaultVibrato() {
    replaceVibrato(Mode2Handler::defaultVibrato);
}

void Mode2Handler::adjustVibrato() {
    if (!hasVBREditor()) {
        return;
    }

    // 预调整：调整三个手柄按钮的纵坐标
    btnPhase->setLocation(m_note->bodyPos());
    btnFrequency->setLocation(m_note->bodyPos().x(), btnPhase->pos().y() + btnPhase->height());
    btnSide->setLocation(m_note->bodyPos().x(), btnPhase->pos().y() - btnSide->height());

    // 限制边界手柄活动范围
    QRect sideRect;
    sideRect.setTopLeft(QPoint(m_note->headPos().x(), btnSide->pos().y()));
    sideRect.setBottomRight(QPoint(m_note->tailPos().x(), btnSide->pos().y()));
    btnSide->setRegion(sideRect);

    // 根据颤音调整边界手柄的位置
    btnSide->setValueX(1 - Vibrato[0] / 100.0);

    // 调整颤音
    updateVibratoLength();
}

void Mode2Handler::adjustVibratoLayer(QWidget *w) {
}

bool Mode2Handler::hasVBREditor() const {
    return VBREditorHolder == this;
}

void Mode2Handler::initVibratoEditor() {
    if (hasVBREditor()) {
        return;
    } else if (VBREditorHolder) {
        VBREditorHolder->removeVibrtoEditor();
    }

    VBREditorHolder = this;

    btnCenter = createLineHandle(Qt::Vertical);
    btnEaseIn = createLineHandle(Qt::Horizontal);
    btnEaseOut = createLineHandle(Qt::Horizontal);
    btnTop = createLineHandle(Qt::Vertical);
    btnBottom = createLineHandle(Qt::Vertical);

    btnSide = createPlaneHandle("S");
    btnPhase = createPlaneHandle("P");
    btnFrequency = createPlaneHandle("F");

    // 边界按钮
    connect(btnSide, &VibratoPlaneHandle::moved, this, &Mode2Handler::updateVibratoLength);
    connect(btnSide, &VibratoPlaneHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    // 相位按钮
    connect(btnPhase, &VibratoPlaneHandle::moved, this, &Mode2Handler::updateVibratoGraph);
    connect(btnPhase, &VibratoPlaneHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    // 频率按钮
    connect(btnFrequency, &VibratoPlaneHandle::moved, this, &Mode2Handler::updateVibratoGraph);
    connect(btnFrequency, &VibratoPlaneHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    // 颤音深度
    connect(btnTop, &VibratoLineHandle::moved, this, &Mode2Handler::updateVibratoHeight);
    connect(btnTop, &VibratoLineHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    connect(btnBottom, &VibratoLineHandle::moved, this, &Mode2Handler::updateVibratoHeight);
    connect(btnBottom, &VibratoLineHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    // 颤音淡入淡出
    connect(btnEaseIn, &VibratoLineHandle::moved, this, &Mode2Handler::updateVibratoEase);
    connect(btnEaseIn, &VibratoLineHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    connect(btnEaseOut, &VibratoLineHandle::moved, this, &Mode2Handler::updateVibratoEase);
    connect(btnEaseOut, &VibratoLineHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    // 颤音高度（偏移）
    connect(btnCenter, &VibratoLineHandle::moved, this, &Mode2Handler::updateVibratoOffset);
    connect(btnCenter, &VibratoLineHandle::clicked, this, &Mode2Handler::saveMovingVibrato);

    adjustVibrato();
}

void Mode2Handler::removeVibrtoEditor() {
    if (!hasVBREditor()) {
        return;
    }
    VBREditorHolder = nullptr;

    removePlaneHandle(btnSide);
    removePlaneHandle(btnPhase);
    removePlaneHandle(btnFrequency);

    btnSide = btnPhase = btnFrequency = nullptr;

    removeLineHandle(btnEaseIn);
    removeLineHandle(btnEaseOut);
    removeLineHandle(btnTop);
    removeLineHandle(btnBottom);
    removeLineHandle(btnCenter);

    btnEaseIn = btnEaseOut = btnTop = btnBottom = btnCenter = nullptr;

    update();
}

void Mode2Handler::fromNotePitches() {
}

void Mode2Handler::toNotePitches() {
}
