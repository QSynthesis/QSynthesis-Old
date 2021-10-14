#include "SectionSettings.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"

using namespace UtaProjectText;

SectionSettings::SectionSettings() {
    clear();
}

void SectionSettings::clear() {
    globalTempo = DEFAULT_VALUE_TEMPO;
    globalFlags = "";
    projectName = "";
    outputFileName = "";
    voiceDirectory = "";
    cacheDirectory = "";
    wavtoolPath = "";
    resamplerPath = "";
    isMode2 = true;
}

bool SectionSettings::operator==(const SectionSettings &another) const {
    return (globalTempo == another.globalTempo) && (globalFlags == another.globalFlags) &&
           (projectName == another.projectName) && (outputFileName == another.outputFileName) &&
           (voiceDirectory == another.voiceDirectory) &&
           (cacheDirectory == another.cacheDirectory) && (wavtoolPath == another.wavtoolPath) &&
           (resamplerPath == another.resamplerPath) && (isMode2 == another.isMode2);
}

bool SectionSettings::operator!=(const SectionSettings &another) const {
    return !((*this) == another);
}
