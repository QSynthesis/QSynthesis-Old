#ifndef VOICEBANKAREA_H
#define VOICEBANKAREA_H

#include <QWidget>

class VoiceBankTab;
class VoiceBankGroup;

class VoiceBankArea : public QWidget {
    Q_OBJECT
public:
    explicit VoiceBankArea(VoiceBankTab *tab, QWidget *parent = nullptr);
    ~VoiceBankArea();

    VoiceBankGroup *ptrs() const;

protected:
    VoiceBankGroup *m_ptrs;
};

#endif // VOICEBANKAREA_H
