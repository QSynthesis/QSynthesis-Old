#include "VoiceBankArea.h"
#include "../../VoiceBankTab.h"

VoiceBankArea::VoiceBankArea(VoiceBankTab *tab, QWidget *parent) : QWidget(parent) {
    m_ptrs = tab->ptrs();
}

VoiceBankArea::~VoiceBankArea() {
}
