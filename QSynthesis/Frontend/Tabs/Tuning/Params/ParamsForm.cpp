#include "ParamsForm.h"
#include "../Scrolls/LiftersScrollArea.h"
#include "../TuningGroup.h"
#include "../TuningTab.h"
#include "Areas/LiftersArea.h"
#include "ParamsInterface.h"

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

    btnInt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    btnMod->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    btnVel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

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

    connect(btnsGroup, &SwitchButtonGroup::oneDoubleClicked, this,
            &ParamsForm::handleSwitchDoubleClicked);
    connect(btnsGroup, &SwitchButtonGroup::switched, this, &ParamsForm::handleSwitchChanged);

    // Pointers
    m_ptrs->paramsContent = content;

    // Set First Status
    btnsGroup->setCurrentIndex(0);
    handleSwitchChanged();
}

TuningGroup *ParamsForm::ptrs() const {
    return m_ptrs;
}

void ParamsForm::handleSwitchChanged() {
    content->setVisionStatus(status());
}

void ParamsForm::handleSwitchDoubleClicked() {
    reverseFold();
}

Params ParamsForm::status() const {
    return static_cast<Params>(btnsGroup->currentIndex());
}

void ParamsForm::setStatus(Params status) {
    if (status == this->status()) {
        return;
    }
    btnsGroup->setCurrentIndex(int(status));
    content->setVisionStatus(status);
}

void ParamsForm::handleUnfolded(bool unfolded) {
    // m_ptrs->liftersScroll->updateSceneRect(m_ptrs->liftersArea->sceneRect());
}
