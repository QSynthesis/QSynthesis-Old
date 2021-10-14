#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/VibratoHandles/VibratoLineHandle.h"
#include "../../Graphics/VibratoHandles/VibratoPlaneHandle.h"
#include "../Mode2Handler.h"

QPointF Mode2Handler::pVibratoStart() const {
    return QPointF(btnSide->pos().x(), btnCenter->position());
}

QPointF Mode2Handler::pVibratoEaseInTop() const {
    return QPointF(btnEaseIn->position(), btnTop->position());
}

QPointF Mode2Handler::pVibratoEaseInBottom() const {
    return QPointF(btnEaseIn->position(), btnBottom->position());
}

QPointF Mode2Handler::pVibratoEaseOutTop() const {
    return QPointF(btnEaseOut->position(), btnTop->position());
}

QPointF Mode2Handler::pVibratoEaseOutBottom() const {
    return QPointF(btnEaseOut->position(), btnBottom->position());
}

QPointF Mode2Handler::pVibratoEaseInCenter() const {
    return QPointF(btnCenter->x(), btnCenter->position());
}

QPointF Mode2Handler::pVibratoEaseOutCenter() const {
    return QPointF(btnCenter->x() + btnCenter->width(), btnCenter->position());
}

QPointF Mode2Handler::pVibratoEnd() const {
    return QPointF(m_note->tailPos().x(), btnCenter->position());
}

QPointF Mode2Handler::pVibratoStandardStart() const {
    return QPointF(btnSide->pos().x(), m_note->headPos().y());
}

QPointF Mode2Handler::pVibratoStandardEnd() const {
    return QPointF(m_note->tailPos().x(), m_note->tailPos().y());
}

VibratoPlaneHandle *Mode2Handler::createPlaneHandle(QString text) {
    VibratoPlaneHandle *btn = new VibratoPlaneHandle(m_editor, this);
    m_editor->addItem(btn);
    btn->setZValue(m_editor->vibratoZIndex);

    btn->setText(text);
    btn->setPadding(2);

    btn->setTopLeft(-9, -9);
    btn->setSize(18, 18);

    return btn;
}

VibratoLineHandle *Mode2Handler::createLineHandle(Qt::Orientation orient) {
    VibratoLineHandle *btn = new VibratoLineHandle(orient, m_editor, this);
    m_editor->addItem(btn);
    btn->setZValue(m_editor->vibratoZIndex);

    btn->setLineWidth(8);
    return btn;
}

void Mode2Handler::removePlaneHandle(VibratoPlaneHandle *p) {
    m_editor->removeItem(p);
    delete p;
}

void Mode2Handler::removeLineHandle(VibratoLineHandle *p) {
    m_editor->removeItem(p);
    delete p;
}
