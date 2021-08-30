#include "TracksForm.h"
#include "../../TuningTab.h"
#include "../Interfaces/TracksInterface.h"
#include "../TuningGroup.h"

using namespace Qs::Panels;

TracksForm::TracksForm(TuningTab *parent) : BaseForm(parent) {
    // Pointer preset
    m_ptrs = parent->ptrs();

    setDefaultTitleBar();
    content = new TracksInterface(this);
    setWidget(content);

    btnTracks = new SwitchButton(tr("Tracks"), titleBar());
    btnConfig = new SwitchButton(tr("Configuration"), titleBar());

    btnTracks->setProperty("type", "titleBar");
    btnConfig->setProperty("type", "titleBar");

    btnsGroup = new SwitchButtonGroup(this);
    btnsGroup->addButton(btnTracks);
    btnsGroup->addButton(btnConfig);

    titleBar()->addItem(btnTracks, false, false);
    titleBar()->addItem(btnConfig, false, false);

    connect(btnsGroup, &SwitchButtonGroup::oneDoubleClicked, this, &BaseForm::reverseFold);
    connect(btnsGroup, &SwitchButtonGroup::switched, this, &TracksForm::handleSwitchChanged);

    // Pointers
    m_ptrs->tracksContent = content;

    // Set First Status
    btnTracks->setChecked(true);
}

TuningGroup *TracksForm::ptrs() const {
    return m_ptrs;
}

Tracks TracksForm::status() const {
    return Tracks(btnsGroup->currentIndex());
}

void TracksForm::setStatus(Tracks status) {
    if (status == this->status()) {
        return;
    }
    btnsGroup->setCurrentIndex(int(status));
    content->setVisionStatus(status);
}

void TracksForm::handleSwitchChanged() {
    content->setVisionStatus(status());
}
