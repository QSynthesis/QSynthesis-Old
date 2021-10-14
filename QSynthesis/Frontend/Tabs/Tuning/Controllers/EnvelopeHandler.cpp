#include "EnvelopeHandler.h"
#include "../Editor/Areas/NotesArea.h"
#include "../Graphics/VolumePoint.h"
#include "../Scrolls/NotesScrollArea.h"

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

void EnvelopeHandler::updateColorTheme() {
    m_envSolidLineEnabledColor = qViewIn->envSolidLineEnabled();
    m_envSolidLineDisabledColor = qViewIn->envSolidLineDisabled();
    m_envDashLineEnabledColor = qViewIn->envDashLineEnabled();
    m_envDashLineDisabledColor = qViewIn->envDashLineDisabled();
    m_envInvalidLineEnabledColor = qViewIn->envInvalidLineEnabled();
    m_envInvalidLineDisabledColor = qViewIn->envInvalidLineDisabled();
    m_pointColor = qViewIn->envPointCore();
    m_ringColor = qViewIn->envPointRing();

    update();
}

void EnvelopeHandler::init() {
    m_type = Qs::Envelopes;

    m_ringWidth = 2;
    m_pointPadding = 2;
    m_pointRadius = 3;

    m_solid = m_editor->envelopesEnabled();
    m_visible = m_editor->envelopesVisible();

    updateColorTheme();
    connect(qViewIn, &NotesScrollArea::envThemeUpdated, this, &EnvelopeHandler::updateColorTheme);
}

GraphicsPoint *EnvelopeHandler::createPointCore() {
    VolumePoint *p = new VolumePoint(this, m_editor);
    p->show();
    m_editor->addItem(p);
    p->setZValue(m_editor->pointZIndex);
    p->setVisible(m_solid);

    return p;
}
