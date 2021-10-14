#include "Mode2Handler.h"
#include "../Editor/Areas/NotesArea.h"
#include "../Scrolls/NotesScrollArea.h"

const QList<QControlPoint> Mode2Handler::defaultPortamento = {QControlPoint(-15, 0),
                                                              QControlPoint(15, 0)};
const QList<double> Mode2Handler::defaultVibrato = {65, 180, 35, 20, 20, 0, 0, 0};

Mode2Handler::Mode2Handler() {
    init();
}

Mode2Handler::Mode2Handler(GraphicsNote *note, NotesArea *editor) : ScopeHandler(note, editor) {
    init();
}

Mode2Handler::~Mode2Handler() {
}

void Mode2Handler::updateColorTheme() {
    m_mode1SolidLineEnabledColor = qViewIn->mode1SolidLineEnabled();
    m_mode2SolidLineEnabledColor = qViewIn->mode2SolidLineEnabled();

    m_mode1SolidLineDisabledColor = qViewIn->mode1SolidLineDisabled();
    m_mode2SolidLineDisabledColor = qViewIn->mode2SolidLineDisabled();

    m_mode1DashLineEnabledColor = qViewIn->mode1DashLineEnabled();
    m_mode2DashLineEnabledColor = qViewIn->mode2DashLineEnabled();

    m_mode1DashLineDisabledColor = qViewIn->mode1DashLineDisabled();
    m_mode2DashLineDisabledColor = qViewIn->mode2DashLineDisabled();

    m_mode2InvalidLineEnabledColor = qViewIn->mode2InvalidLineEnabled();
    m_mode2InvalidLineDisabledColor = qViewIn->mode2InvalidLineDisabled();

    m_vibratoEnabledColor = qViewIn->vbrCurvesEnabled();
    m_vibratoDisabledColor = qViewIn->vbrCurvesDisabled();

    m_vibratoEditorLinesColor = qViewIn->vbrEditorLines();

    m_pointColor = qViewIn->mode2PointCore();
    m_ringColor = qViewIn->mode2PointRing();

    update();
}

void Mode2Handler::init() {
    m_type = Qs::Mode2;

    m_ringWidth = 2;
    m_pointPadding = 2;
    m_pointRadius = 3;

    m_solid = m_editor->pitchesEnabled();
    m_visible = m_editor->pitchesVisible();

    updateColorTheme();
    connect(qViewIn, &NotesScrollArea::pitchThemeUpdated, this, &Mode2Handler::updateColorTheme);
}
