#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <QColor>
#include <QDebug>

#include "Macros.h"

class ColorTheme {
    Q_SINGLETON(ColorTheme)

public:
    explicit ColorTheme();
    virtual ~ColorTheme();

    static void previewTheme(int index);

    // NotesArea
public:
    QColor editor_quarterLine;
    QColor editor_timeLine;
    QColor editor_sectionLine;
    QColor editor_pitchLine;
    QColor editor_levelLine;
    QColor editor_backDark;
    QColor editor_backLight;

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

    QColor pitch_vibratoButtonBorder;
    QColor pitch_vibratoButtonFill;
    QColor pitch_vibratoFrame;

    // GraphicsNote
public:
    QColor note_lyric;

    QColor note_restFill;
    QColor note_restLine;

    QColor note_listedFill;
    QColor note_listedLine;

    QColor note_unlistedFill;
    QColor note_unlistedLine;

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
};

#endif // COLORTHEME_H
