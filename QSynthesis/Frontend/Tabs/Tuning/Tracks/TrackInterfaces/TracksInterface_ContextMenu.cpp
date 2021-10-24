#include "../../TuningGroup.h"
#include "../TracksForm.h"
#include "../TracksInterface.h"

void TracksInterface::handleMenuBtnClicked() {
    m_ptrs->tab->tabActions->tracksMenu->exec(btnMenu->mapToGlobal(btnMenu->rect().center()));
}
