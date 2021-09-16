#include "ColorTheme.h"

Q_SINGLETON_DECLARE(ColorTheme)

ColorTheme::ColorTheme(QObject *parent) : QObject(parent) {
    initDark();
}

ColorTheme::~ColorTheme() {
}

void ColorTheme::previewTheme(int index) {
}

void ColorTheme::update() {
    emit updated();
}

void ColorTheme::initLight() {
    // NotesArea
    editor_quarterLine = QColor(0xD4D4D4);
    editor_timeLine = QColor(0xE2E2E2);
    editor_sectionLine = QColor(0xBFBFBF);
    editor_pitchLine = QColor(0xE6E6E6);
    editor_levelLine = QColor(0xCCCCCC);
    editor_backDark = QColor(0xF2F2F2);
    editor_backLight = QColor(0xFFFFFF);
    editor_playHead = Qt::black;

    // LiftersArea
    params_timeLine = QColor(0xD4D4D4);
    params_sectionLine = QColor(0xBFBFBF);
    params_back =  QColor(0xFFFFFF);

    // GraphicsNote
    note_lyric = Qt::black;
    note_restLine = QColor(0xCCCCCC);
    note_restFill = QColor(0xEEEEEE);
    note_listedLine = QColor(0x0099FF);
    note_listedFill = QColor(0x40D9FF);
    note_unlistedLine = QColor(0x105685);
    note_unlistedFill = QColor(0x1881C7);
    note_select = QColor(0, 0, 0, 48);

    // GraphicsLifter
    lifter_active = QColor(0x79BBEE);
    lifter_inactive = Qt::gray;
    lifter_activeH = QColor(QColorConstants::Svg::pink);
    lifter_inactiveH = Qt::lightGray;

    // GraphicsRubber
    rubber_frame = Qt::black;
    rubber_fill = QColor(0, 0, 0, 120);

    // Mode2Handler
    pitch_mode1SolidLineEnabled = Qt::red;
    pitch_mode2SolidLineEnabled = Qt::red;

    pitch_mode1DashLineEnabled = QColor(0xFF, 0, 0, 192);
    pitch_mode2DashLineEnabled = QColor(0xFF, 0, 0, 192);

    pitch_mode1SolidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    pitch_mode2SolidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    pitch_mode1DashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    pitch_mode2DashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    pitch_mode2InvalidLineEnabled = QColor(0xFF, 0, 0, 72);
    pitch_mode2InvalidLineDisabled = QColor(0xFF, 0, 0, 30);

    vibrato_curvesEnabledColor = pitch_mode2SolidLineEnabled;
    vibrato_curvesDisabledColor = pitch_mode2SolidLineDisabled;

    vibrato_editorLines = QColor(0x232323);

    pitch_pointCore = pitch_mode2SolidLineEnabled;
    pitch_pointRing = pitch_mode2SolidLineEnabled;

    // EnvelopeHandler
    env_solidLineEnabled = Qt::blue;
    env_dashLineEnabled = QColor(0, 0, 0xFF, 192);

    env_solidLineDisabled = QColor(0x80, 0x80, 0xFF, 192);
    env_dashLineDisabled = QColor(0x80, 0x80, 0xFF, 192);

    env_invalidLineEnabled = QColor(0, 0, 0xFF, 72);
    env_invalidLineDisabled = QColor(0, 0, 0xFF, 30);

    env_pointCore = Qt::blue;
    env_pointRing = Qt::blue;
}

void ColorTheme::initDark() {
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
    pitch_mode1SolidLineEnabled = QColor(255, 77, 77);
    pitch_mode2SolidLineEnabled = QColor(255, 77, 77);

    pitch_mode1DashLineEnabled = QColor(255, 77, 77, 192);
    pitch_mode2DashLineEnabled = QColor(255, 77, 77, 192);

    pitch_mode1SolidLineDisabled = QColor(255, 128, 128, 192);
    pitch_mode2SolidLineDisabled = QColor(255, 128, 128, 192);

    pitch_mode1DashLineDisabled = QColor(255, 128, 128, 128);
    pitch_mode2DashLineDisabled = QColor(255, 128, 128, 128);

    pitch_mode2InvalidLineEnabled = QColor(255, 77, 77, 72);
    pitch_mode2InvalidLineDisabled = QColor(255, 77, 77, 36);

    vibrato_curvesEnabledColor = pitch_mode2SolidLineEnabled;
    vibrato_curvesDisabledColor = pitch_mode2SolidLineDisabled;

    vibrato_editorLines = Qt::yellow;

    pitch_pointCore = pitch_mode2SolidLineEnabled;
    pitch_pointRing = pitch_mode2SolidLineEnabled;

    // EnvelopeHandler
    env_solidLineEnabled = QColor(150, 216, 216);
    env_solidLineDisabled = QColor(150, 216, 216, 128);

    env_dashLineEnabled = QColor(150, 216, 216, 192);
    env_dashLineDisabled = QColor(150, 216, 216, 96);

    env_invalidLineEnabled = QColor(150, 216, 216, 72);
    env_invalidLineDisabled = QColor(150, 216, 216, 36);

    env_pointCore = env_solidLineEnabled;
    env_pointRing = env_solidLineEnabled;
}
