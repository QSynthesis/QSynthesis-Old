#include "SectionVersion.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"

using namespace UtaProjectText;

// Project File Version
SectionVersion::SectionVersion() {
    clear();
}

void SectionVersion::clear() {
    version = UST_VERSION_1_2;
    charset = "";
}

// Project File Notes
bool SectionVersion::operator==(const SectionVersion &another) const {
    return (version == another.version);
}

bool SectionVersion::operator!=(const SectionVersion &another) const {
    return !((*this) == another);
}
