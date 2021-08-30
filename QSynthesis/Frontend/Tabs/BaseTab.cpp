#include "BaseTab.h"
#include "mainwindow.h"

BaseTab::BaseTab(TabWidget *parent) : QWidget(parent), m_parent(parent) {
    setAttribute(Qt::WA_StyledBackground);
}

TabWidget *BaseTab::parentTabWidget() const {
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

BaseTab::~BaseTab() {
}
