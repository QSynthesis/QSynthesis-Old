#include "FindOption.h"

FindOption::FindOption() : matchCase(false), matchWord(false) {
}

FindOption::FindOption(const QString &text, bool bCase, bool bWord)
    : findText(text), matchCase(bCase), matchWord(bWord) {
}

FindOption::~FindOption() {
}

bool FindOption::match(const QString &text) {
    Qt::CaseSensitivity sense = matchCase ? Qt::CaseSensitive : Qt::CaseInsensitive;
    return !findText.isEmpty() &&
           (matchWord ? (!text.compare(findText, sense)) : text.contains(findText, sense));
}

ReplaceOption::ReplaceOption() : preserveCase(false) {
}

ReplaceOption::ReplaceOption(const QString &text, bool bPreserve)
    : replaceText(text), preserveCase(bPreserve) {
}

ReplaceOption::~ReplaceOption() {
}
