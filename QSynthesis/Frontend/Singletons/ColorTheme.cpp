#include "ColorTheme.h"

Q_SINGLETON_DECLARE(ColorTheme)

ColorTheme::ColorTheme(QObject *parent) : QObject(parent) {
    // NotesArea
    editor_quarterLine = QColor(0x161616);
    editor_timeLine = QColor(0x1C1C1C);
    editor_sectionLine = QColor(0x101010);
    editor_pitchLine = QColor(0x101010);
    editor_levelLine = QColor(0x191919);
    editor_backDark = QColor(0x232323);
    editor_backLight = QColor(0x2D2D2D);
    editor_playHead = Qt::white;

    // LiftersArea
    params_timeLine = QColor(0x1C1C1C);
    params_sectionLine = QColor(0x101010);
    params_back = QColor(0x2D2D2D);

    // GraphicsNote
    note_lyric = Qt::white;
    note_restLine = QColor(0xCCCCCC);
    note_restFill = QColor(0xEEEEEE);
    note_listedLine = QColor(0x0099FF);
    note_listedFill = QColor(0x40D9FF);
    note_unlistedLine = QColor(0x105685);
    note_unlistedFill = QColor(0x1881C7);
    note_select = QColor(255, 255, 255, 48);

    // GraphicsLifter
    lifter_active = QColor(0x79BBEE);
    lifter_inactive = Qt::gray;
    lifter_activeH = QColor(QColorConstants::Svg::pink);
    lifter_inactiveH = Qt::lightGray;

    // GraphicsRubber
    rubber_frame = QColor(255, 255, 255, 96);
    rubber_fill = QColor(255, 255, 255, 48);

    // Mode2Handler
    pitch_mode1SolidLineEnabled = Qt::red;
    pitch_mode2SolidLineEnabled = Qt::red;

    pitch_mode1SolidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    pitch_mode2SolidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    pitch_mode1DashLineEnabled = QColor(0xFF, 0, 0, 192);
    pitch_mode2DashLineEnabled = QColor(0xFF, 0, 0, 192);

    pitch_mode1DashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    pitch_mode2DashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    pitch_mode2InvalidLineEnabled = QColor(0xFF, 0, 0, 72);
    pitch_mode2InvalidLineDisabled = QColor(0xFF, 0, 0, 30);

    vibrato_curvesEnabledColor = Qt::red;
    vibrato_curvesDisabledColor = QColor(0xFF, 0x80, 0x80, 192);

    vibrato_editorLines = QColor(0x232323);

    pitch_pointCore = Qt::red;
    pitch_pointRing = Qt::red;

    // EnvelopeHandler
    env_solidLineEnabled = QColorConstants::Svg::lightblue;
    env_solidLineDisabled = QColor(0x80, 0x80, 0xFF, 192);

    env_dashLineEnabled = QColor(env_solidLineEnabled.red(), env_solidLineEnabled.green(),
                                 env_solidLineEnabled.blue(), 192);
    env_dashLineDisabled = QColor(0x80, 0x80, 0xFF, 192);

    env_invalidLineEnabled = QColor(env_solidLineEnabled.red(), env_solidLineEnabled.green(),
                                    env_solidLineEnabled.blue(), 72);
    env_invalidLineDisabled = QColor(env_solidLineEnabled.red(), env_solidLineEnabled.green(),
                                     env_solidLineEnabled.blue(), 30);

    env_pointCore = QColorConstants::Svg::lightblue;
    env_pointRing = QColorConstants::Svg::lightblue;
}

ColorTheme::~ColorTheme() {
}

void ColorTheme::previewTheme(int index) {
}

void ColorTheme::update() {
    emit updated();
}
