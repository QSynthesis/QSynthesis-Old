#include "ParamsForm.h"
#include "../../TuningTab.h"
#include "../Interfaces/ParamsInterface.h"
#include "../TuningGroup.h"

using namespace Qs::Panels;

ParamsForm::ParamsForm(TuningTab *parent) : BaseForm(parent) {
    // Pointer preset
    m_ptrs = parent->ptrs();

    setDefaultTitleBar();
    content = new ParamsInterface(this);
    setWidget(content);

    btnInt = new SwitchButton(tr("Intensity"), titleBar());
    btnMod = new SwitchButton(tr("Modulation"), titleBar());
    btnVel = new SwitchButton(tr("Velocity"), titleBar());

    btnInt->setProperty("type", "titleBar");
    btnMod->setProperty("type", "titleBar");
    btnVel->setProperty("type", "titleBar");

    btnsGroup = new SwitchButtonGroup(this);
    btnsGroup->addButton(btnInt);
    btnsGroup->addButton(btnMod);
    btnsGroup->addButton(btnVel);

    titleBar()->addItem(btnInt, false, false);
    titleBar()->addItem(btnMod, false, false);
    titleBar()->addItem(btnVel, false, false);

    connect(btnsGroup, &SwitchButtonGroup::oneDoubleClicked, this, &BaseForm::reverseFold);
    connect(btnsGroup, &SwitchButtonGroup::switched, this, &ParamsForm::handleSwitchChanged);

    // Pointers
    m_ptrs->paramsContent = content;

    // Set First Status
    btnInt->setChecked(true);
}

TuningGroup *ParamsForm::ptrs() const {
    return m_ptrs;
}

void ParamsForm::handleSwitchChanged() {
    content->setVisionStatus(status());
}

Params ParamsForm::status() const {
    return Params(btnsGroup->currentIndex());
}

void ParamsForm::setStatus(Params status) {
    if (status == this->status()) {
        return;
    }
    btnsGroup->setCurrentIndex(int(status));
    content->setVisionStatus(status);
}
