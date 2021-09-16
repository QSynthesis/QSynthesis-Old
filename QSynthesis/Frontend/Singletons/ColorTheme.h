#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <QColor>
#include <QDebug>

#include "Macros.h"

class NotesArea;
class Mode2Handler;
class EnvelopeHandler;
class GraphicsNote;
class WaveformArea;

class ColorTheme : public QObject {
    Q_OBJECT
    Q_SINGLETON(ColorTheme)

public:
    explicit ColorTheme(QObject *parent = nullptr);
    virtual ~ColorTheme();

    static void previewTheme(int index);

    void update();

private:
    void initLight();
    void initDark();

    // NotesArea
public:
    QColor editor_quarterLine;
    QColor editor_timeLine;
    QColor editor_sectionLine;
    QColor editor_pitchLine;
    QColor editor_levelLine;
    QColor editor_backDark;
    QColor editor_backLight;

    QColor editor_playHead;

    // LiftersArea
public:
    QColor params_timeLine;
    QColor params_sectionLine;
    QColor params_back;

    // Mode2Handler
public:
    QColor pitch_mode1SolidLineEnabled;
    QColor pitch_mode2SolidLineEnabled;

    QColor pitch_mode1SolidLineDisabled;
    QColor pitch_mode2SolidLineDisabled;

    QColor pitch_mode1DashLineEnabled;
    QColor pitch_mode2DashLineEnabled;

    QColor pitch_mode1DashLineDisabled;
    QColor pitch_mode2DashLineDisabled;

    QColor pitch_mode2InvalidLineEnabled;
    QColor pitch_mode2InvalidLineDisabled;

    QColor vibrato_curvesEnabledColor;
    QColor vibrato_curvesDisabledColor;

    QColor vibrato_editorLines;

    QColor pitch_pointCore;
    QColor pitch_pointRing;

    // Vibrato Plane Handle
public:
    QColor vbr_planeHandleBorder;
    QColor vbr_planeHandleFill;
    QColor vbr_planeHandleText;

    // EnvelopeHandler
public:
    QColor env_solidLineEnabled;
    QColor env_solidLineDisabled;

    QColor env_dashLineEnabled;
    QColor env_dashLineDisabled;

    QColor env_invalidLineEnabled;
    QColor env_invalidLineDisabled;

    QColor env_pointCore;
    QColor env_pointRing;

    // GraphicsNote
public:
    QColor note_lyric;

    QColor note_restFill;
    QColor note_restLine;

    QColor note_listedFill;
    QColor note_listedLine;

    QColor note_unlistedFill;
    QColor note_unlistedLine;

    QColor note_select;

    // GraphicsLifter
public:
    QColor lifter_active;
    QColor lifter_inactive;

    QColor lifter_activeH;
    QColor lifter_inactiveH;

public:
    QColor rubber_frame;
    QColor rubber_fill;

    // WaveformArea
public:
    QColor sample_offsetLine;
    QColor sample_constantLine;
    QColor sample_blankLine;
    QColor sample_preUttrLine;
    QColor sample_overlapLine;

    QColor sample_offsetBack;
    QColor sample_constantBack;
    QColor sample_blankBack;

    QColor sample_waveform;
    QColor sample_frqCurves;

signals:
    void updated();
};

#endif // COLORTHEME_H
