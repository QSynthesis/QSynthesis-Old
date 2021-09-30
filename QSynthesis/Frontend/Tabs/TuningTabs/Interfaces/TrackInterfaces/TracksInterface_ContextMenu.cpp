#include "../../Forms/TracksForm.h"
#include "../../TuningGroup.h"
#include "../TracksInterface.h"

void TracksInterface::handleMenuBtnClicked() {
    m_ptrs->tab->tabActions->tracksMenu->exec(QCursor::pos());
}
