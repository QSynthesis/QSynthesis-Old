#ifndef FINDOPTION_H
#define FINDOPTION_H

#include <QString>

class FindOption {
public:
    FindOption();
    FindOption(const QString &text, bool bCase, bool bWord);

    ~FindOption();

    QString findText;
    bool matchCase;
    bool matchWord;

    bool match(const QString &text);
};

class ReplaceOption {
public:
    ReplaceOption();
    ReplaceOption(const QString &text, bool bPreserve);
    ~ReplaceOption();

    QString replaceText;
    bool preserveCase;
};

#endif // FINDOPTION_H
