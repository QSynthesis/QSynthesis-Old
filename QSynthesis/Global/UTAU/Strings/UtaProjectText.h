#ifndef UTAPROJECTTEXT_H
#define UTAPROJECTTEXT_H

#include <QString>

namespace UtaProjectText {

    // Sections
    const QString SECTION_BEGIN_MARK = "[#";
    const QString SECTION_END_MARK = "]";
    const QString SECTION_NAME_DELETE = "DELETE";
    const QString SECTION_NAME_INSERT = "INSERT";
    const QString SECTION_NAME_NEXT = "NEXT";
    const QString SECTION_NAME_PREV = "PREV";
    const QString SECTION_NAME_SETTING = "SETTING";
    const QString SECTION_NAME_VERSION = "VERSION";
    const QString SECTION_NAME_TRACKEND = "TRACKEND"; // Add

    // Keys
    const QString KEY_NAME_CHARSET = "Charset"; // Add
    const QString KEY_NAME_PROJECT = "Project"; // Add
    const QString KEY_NAME_CACHE_DIR = "CacheDir";
    const QString KEY_NAME_DIRECT = "$direct";
    const QString KEY_NAME_ENVELOPE = "Envelope";
    const QString KEY_NAME_FLAGS = "Flags";
    const QString KEY_NAME_INTENSITY = "Intensity";
    const QString KEY_NAME_LENGTH = "Length";
    const QString KEY_NAME_LYRIC = "Lyric";
    const QString KEY_NAME_MODULATION = "Modulation";
    const QString KEY_NAME_MODURATION = "Moduration";
    const QString KEY_NAME_NOTE_NUM = "NoteNum";
    const QString KEY_NAME_PBM = "PBM";
    const QString KEY_NAME_PBS = "PBS";
    const QString KEY_NAME_PB_TYPE = "PBType";
    const QString KEY_NAME_PB_START = "PBStart"; // Add
    const QString KEY_NAME_PBW = "PBW";
    const QString KEY_NAME_PBY = "PBY";
    const QString KEY_NAME_PICHES = "Piches";
    const QString KEY_NAME_PITCHES = "Pitches";
    const QString KEY_NAME_PITCH_BEND = "PitchBend"; // Add
    const QString KEY_NAME_PRE_UTTERANCE = "PreUtterance";
    const QString KEY_NAME_START_POINT = "StartPoint";
    const QString KEY_NAME_TEMPO = "Tempo";
    const QString KEY_NAME_VBC = "VBC";
    const QString KEY_NAME_VBR = "VBR";
    const QString KEY_NAME_VELOCITY = "Velocity";
    const QString KEY_NAME_VOICE_DIR = "VoiceDir";
    const QString KEY_NAME_VOICE_OVERLAP = "VoiceOverlap";

    // Other Keys
    const QString KEY_NAME_PROJECT_NAME = "ProjectName"; // Add
    const QString KEY_NAME_TRACKS = "Tracks";            // Add
    const QString KEY_NAME_OUTPUT_FILE = "OutFile";      // Add
    const QString KEY_NAME_MODE2 = "Mode2";              // Add
    const QString KEY_NAME_TOOL1 = "Tool1";              // Add
    const QString KEY_NAME_TOOL2 = "Tool2";              // Add

    const QString KEY_NAME_PRE_UTTERANCE_READONLY = "@preuttr";
    const QString KEY_NAME_VOICE_OVERLAP_READONLY = "@overlap";
    const QString KEY_NAME_START_POINT_READONLY = "@stpoint";

    const QString KEY_NAME_FILENAME_READONLY = "@filename";
    const QString KEY_NAME_ALIAS_READONLY = "@alias";
    const QString KEY_NAME_CACHE_READONLY = "@cache";

    const QString KEY_NAME_PATCH = "$patch";
    const QString KEY_NAME_REGION_START = "$region";
    const QString KEY_NAME_REGION_END = "$region_end";

    const QString KEY_NAME_LABEL = "Label";

    // Head
    const QString UST_VERSION_PREFIX = "UST Version ";
    const QString UST_VERSION_PREFIX_NOSPACE = "UST Version";

} // namespace UtaProjectText

#endif // UTAPROJECTTEXT_H
