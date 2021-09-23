#include "../CentralTabWidget.h"

int CentralTabWidget::addTab(CentralTab *tab, const QString &label) {
    return TabWidget::addTab(tab, label);
}

int CentralTabWidget::addTab(CentralTab *tab, const QIcon &icon, const QString &label) {
    return TabWidget::addTab(tab, icon, label);
}

int CentralTabWidget::insertTab(int index, CentralTab *tab, const QString &label) {
    return TabWidget::insertTab(index, tab, label);
}

int CentralTabWidget::insertTab(int index, CentralTab *tab, const QIcon &icon,
                                const QString &label) {
    return TabWidget::insertTab(index, tab, icon, label);
}

CentralTab *CentralTabWidget::currentWidget() const {
    return qobject_cast<CentralTab *>(TabWidget::currentWidget());
}

CentralTab *CentralTabWidget::tabAt(int index) const {
    return qobject_cast<CentralTab *>(TabWidget::tabAt(index));
}

int CentralTabWidget::indexOf(CentralTab *tab) const {
    return TabWidget::indexOf(tab);
}

void CentralTabWidget::setCornerWidget(CentralTab *w, Qt::Corner corner) {
    return TabWidget::setCornerWidget(w, corner);
}

CentralTab *CentralTabWidget::cornerWidget(Qt::Corner corner) const {
    return qobject_cast<CentralTab *>(TabWidget::cornerWidget(corner));
}

void CentralTabWidget::setCurrentWidget(CentralTab *tab) {
    return TabWidget::setCurrentWidget(tab);
}

void CentralTabWidget::removeTab(int index) {
    return TabWidget::removeTab(index);
}

void CentralTabWidget::removeTab(CentralTab *tab) {
    return TabWidget::removeTab(tab);
}

CentralTab *CentralTabWidget::currentTab() const {
    return qobject_cast<CentralTab *>(TabWidget::currentTab());
}

CentralTab *CentralTabWidget::previousTab() const {
    return qobject_cast<CentralTab *>(TabWidget::previousTab());
}
