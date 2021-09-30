#include "BaseTab.h"
#include "TabWidget.h"

BaseTab::BaseTab(TabWidget *parent) : MoreWidget(parent), m_parent(parent) {
    m_active = false;
}

BaseTab::~BaseTab() {
}

void BaseTab::enter() {
    m_active = true;
}

void BaseTab::leave() {
    m_active = false;
}

TabWidget *BaseTab::tabWidget() const {
    return m_parent;
}

QString BaseTab::tabName() const {
    return m_tabName;
}

void BaseTab::setTabName(const QString &value) {
    m_tabName = value;
    emit tabNameChanged(value);
}

void BaseTab::updateTabName() {
    setTabName(m_tabName);
}

bool BaseTab::active() const {
    return m_active;
}
