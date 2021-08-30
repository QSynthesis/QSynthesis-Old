#include "EnvelopeHandler.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Graphics/VolumePoint.h"

const QList<QControlPoint> EnvelopeHandler::defaultEnvelope = {
    QControlPoint(0, 0), QControlPoint(5, 100), QControlPoint(35, 100), QControlPoint(0, 0)};

EnvelopeHandler::EnvelopeHandler() {
    init();
}

EnvelopeHandler::EnvelopeHandler(GraphicsNote *note, NotesArea *editor)
    : ScopeHandler(note, editor) {
    init();
}

EnvelopeHandler::~EnvelopeHandler() {
}

void EnvelopeHandler::init() {
    m_type = Qs::Envelopes;

    m_envSolidLineEnabledColor = Qt::blue;
    m_envSolidLineDisabledColor = QColor(0x80, 0x80, 0xFF, 192);

    m_envDashLineEnabledColor = QColor(0, 0, 0xFF, 192);
    m_envDashLineDisabledColor = QColor(0x80, 0x80, 0xFF, 192);

    m_envInvalidLineEnabledColor = QColor(0, 0, 0xFF, 72);
    m_envInvalidLineDisabledColor = QColor(0, 0, 0xFF, 30);

    m_ringWidth = 2;
    m_pointPadding = 2;
    m_pointRadius = 3;

    m_pointColor = Qt::blue;
    m_ringColor = Qt::blue;
}

GraphicsPoint *EnvelopeHandler::createPointCore() {
    VolumePoint *p = new VolumePoint(this, m_editor);
    p->show();
    m_editor->addItem(p);
    p->setZValue(m_editor->pointZIndex);
    p->setVisible(m_solid);

    return p;
}
