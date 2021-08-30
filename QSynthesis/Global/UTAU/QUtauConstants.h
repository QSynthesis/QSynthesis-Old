#ifndef QUTAUCONSTANTS_H
#define QUTAUCONSTANTS_H

#include <QString>

const QString TONE_NAMES = "CCDDEFFGGAAB";
const QString TONE_NAME_SHARP = "#";

const QString LYRIC_R = "R";

const int TIME_BASE = 480;
const int TONE_NUMBER_BASE = 24;
const int TONE_OCTAVE_MAX = 7;
const int TONE_OCTAVE_MIN = 1;
const int TONE_OCTAVE_STEPS = 12;

const int NUM_ENVELOPE_POINTS = 5;

// Default Values
const double DEFAULT_VALUE_INTENSITY = 100.0;
const double DEFAULT_VALUE_MODULATION = 100.0; // Add
const double DEFAULT_VALUE_PRE_UTTERANCE = 0.0;
const double DEFAULT_VALUE_TEMPO = 120.0;
const double DEFAULT_VALUE_VOICE_OVERLAP = 0.0;
const double DEFAULT_START_POINT = 0.0; // Add

const double DEFAULT_VALUE_VELOCITY = 100;
const double DEFAULT_VALUE_START_POINT = 0;
const QString DEFAULT_VALUE_FLAGS = "";

const QString VALUE_MODE2_ON = "True";
const QString VALUE_TRACKS_SINGLE = "1";
const QString VALUE_PITCH_TYPE = "5";

// Mark Values
const QString DELETE_STRING = "%DELETE%";
const QString NODEF_STRING = "%NODEF%";

const int NODEF_INT = INT_MIN;
const double NODEF_DOUBLE = -1e+08;

#endif // QUTAUCONSTANTS_H
