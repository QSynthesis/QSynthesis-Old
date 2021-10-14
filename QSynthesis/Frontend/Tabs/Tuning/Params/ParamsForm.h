#ifndef PARAMSFORM_H
#define PARAMSFORM_H

#include <QWidget>

#include "../Base/BaseForm.h"
#include "Controls/Buttons/SwitchButton.h"
#include "Types.h"

class TuningTab;
class TuningGroup;
class ParamsInterface;

class ParamsForm : public BaseForm {
    Q_OBJECT
public:
    explicit ParamsForm(TuningTab *parent = nullptr);

    TuningGroup *ptrs() const;
    Qs::Panels::Params status() const;
    void setStatus(Qs::Panels::Params status);

private:
    SwitchButton *btnInt, *btnMod, *btnVel;
    SwitchButtonGroup *btnsGroup;

    ParamsInterface *content;
    TuningGroup *m_ptrs;

    void handleUnfolded(bool unfolded) override;

private:
    void handleSwitchChanged();
    void handleSwitchDoubleClicked();
signals:
};

#endif // PARAMSFORM_H
