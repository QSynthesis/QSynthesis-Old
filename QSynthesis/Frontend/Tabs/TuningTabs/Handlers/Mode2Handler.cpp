#include "Mode2Handler.h"
#include "mainwindow.h"

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
    m_mode1SolidLineEnabledColor = qTheme->pitch_mode1SolidLineEnabled;
    m_mode2SolidLineEnabledColor = qTheme->pitch_mode2SolidLineEnabled;

    m_mode1SolidLineDisabledColor = qTheme->pitch_mode1SolidLineDisabled;
    m_mode2SolidLineDisabledColor = qTheme->pitch_mode2SolidLineDisabled;

    m_mode1DashLineEnabledColor = qTheme->pitch_mode1DashLineEnabled;
    m_mode2DashLineEnabledColor = qTheme->pitch_mode2DashLineEnabled;

    m_mode1DashLineDisabledColor = qTheme->pitch_mode1DashLineDisabled;
    m_mode2DashLineDisabledColor = qTheme->pitch_mode2DashLineDisabled;

    m_mode2InvalidLineEnabledColor = qTheme->pitch_mode2InvalidLineEnabled;
    m_mode2InvalidLineDisabledColor = qTheme->pitch_mode2InvalidLineDisabled;

    m_vibratoEnabledColor = qTheme->vibrato_curvesEnabledColor;
    m_vibratoDisabledColor = qTheme->vibrato_curvesDisabledColor;

    m_vibratoEditorLinesColor = qTheme->vibrato_editorLines;

    m_pointColor = qTheme->pitch_pointCore;
    m_ringColor = qTheme->pitch_pointRing;

    update();
}

void Mode2Handler::init() {
    m_type = Qs::Mode2;

    m_ringWidth = 2;
    m_pointPadding = 2;
    m_pointRadius = 3;

    updateColorTheme();
    connect(qTheme, &ColorTheme::updated, this, &Mode2Handler::updateColorTheme);
}
