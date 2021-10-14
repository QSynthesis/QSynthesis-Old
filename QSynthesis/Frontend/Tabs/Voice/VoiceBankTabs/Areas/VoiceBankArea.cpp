#include "VoiceBankArea.h"
#include "../../VoiceBankTab.h"

VoiceBankArea::VoiceBankArea(VoiceBankTab *tab,QWidget *parent) : MoreWidget(parent) {
    m_ptrs = tab->ptrs();
}

VoiceBankArea::~VoiceBankArea() {
}
