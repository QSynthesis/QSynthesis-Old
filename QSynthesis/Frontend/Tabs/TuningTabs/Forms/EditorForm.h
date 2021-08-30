#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

#include "BaseForm.h"
#include "Controls/SwitchButton.h"
#include "QUtils.h"

#include "../Modules/Buttons/EnvButtonGroup.h"
#include "../Modules/Buttons/PlayButtonGroup.h"

class TuningTab;
class TuningGroup;
class EditorInterface;

class EditorForm : public BaseForm {
    Q_OBJECT
public:
    explicit EditorForm(TuningTab *parent = nullptr);

    TuningGroup *ptrs() const;

    Qs::Panels::Editor status() const;
    void setStatus(Qs::Panels::Editor status);

private:
    SwitchButton *btnNote, *btnPitch, *btnEnvelope;
    SwitchButtonGroup *btnsGroup;

    PlayButtonGroup *btnPlays;
    EnvButtonGroup *btnEases;

    EditorInterface *content;
    TuningGroup *m_ptrs;

public:
    void updatePlayStatus(bool playing);

private:
    void handleSwitchChanged();

    void onPlay();
    void onStop();
    void onStart();
    void onEnd();

    void onEnvP2P3();
    void onEnvP1P4();
    void onEnvReset();

signals:
};

#endif // EDITORFORM_H
