#ifndef PROPERTIESFORM_H
#define PROPERTIESFORM_H

#include <QWidget>

#include "BaseForm.h"
#include "Controls/SwitchButton.h"

class TuningTab;
class TuningGroup;
class TracksInterface;

class TracksForm : public BaseForm {
    Q_OBJECT
public:
    explicit TracksForm(TuningTab *parent = nullptr);

    TuningGroup *ptrs() const;

    Qs::Panels::Tracks status() const;
    void setStatus(Qs::Panels::Tracks status);

private:
    SwitchButton *btnTracks, *btnConfig;
    SwitchButtonGroup *btnsGroup;

    TracksInterface *content;
    TuningGroup *m_ptrs;

    void handleSwitchChanged();
signals:
};

#endif // PROPERTIESFORM_H
