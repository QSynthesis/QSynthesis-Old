#include "TabWidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
}

TabWidget::~TabWidget() {
}

int TabWidget::addTab(BaseTab *tab, const QString &label) {
    connect(tab, &BaseTab::tabNameChanged, this, &TabWidget::handleTabNameChanged);
    int res = QTabWidget::addTab(tab, label);
    addTabCore(res);

    return res;
}

int TabWidget::addTab(BaseTab *tab, const QIcon &icon, const QString &label) {
    connect(tab, &BaseTab::tabNameChanged, this, &TabWidget::handleTabNameChanged);
    int res = QTabWidget::addTab(tab, icon, label);
    addTabCore(res);

    return res;
}

int TabWidget::insertTab(int index, BaseTab *tab, const QString &label) {
    connect(tab, &BaseTab::tabNameChanged, this, &TabWidget::handleTabNameChanged);
    int res = QTabWidget::insertTab(index, tab, label);
    addTabCore(res);

    return res;
}

int TabWidget::insertTab(int index, BaseTab *tab, const QIcon &icon, const QString &label) {
    connect(tab, &BaseTab::tabNameChanged, this, &TabWidget::handleTabNameChanged);
    int res = QTabWidget::insertTab(index, tab, icon, label);
    addTabCore(res);

    return res;
}

BaseTab *TabWidget::currentWidget() const {
    return qobject_cast<BaseTab *>(QTabWidget::currentWidget());
}

BaseTab *TabWidget::tabAt(int index) const {
    return qobject_cast<BaseTab *>(QTabWidget::widget(index));
}

int TabWidget::indexOf(BaseTab *tab) const {
    return QTabWidget::indexOf(tab);
}

void TabWidget::setCornerWidget(BaseTab *w, Qt::Corner corner) {
    return QTabWidget::setCornerWidget(w, corner);
}

BaseTab *TabWidget::cornerWidget(Qt::Corner corner) const {
    return qobject_cast<BaseTab *>(QTabWidget::cornerWidget(corner));
}

void TabWidget::setCurrentWidget(BaseTab *tab) {
    return QTabWidget::setCurrentWidget(tab);
}

void TabWidget::setTabTitle(int index, const QString &title) {
    setTabText(index, title);
    emit titleChanged(index, title);
}

QString TabWidget::currentTitle() const {
    return tabText(currentIndex());
}

void TabWidget::removeTab(int index) {
    BaseTab *tab = tabAt(index);
    disconnect(tab, &BaseTab::tabNameChanged, this, &TabWidget::handleTabNameChanged);
    removeTabCore(index);
    QTabWidget::removeTab(index);
}

void TabWidget::removeTab(BaseTab *tab) {
    int index = indexOf(tab);
    if (index < 0) {
        return;
    }
    removeTab(index);
    removeTabCore(index);
}

void TabWidget::addTabCore(int index) {
}

void TabWidget::removeTabCore(int index) {
}

void TabWidget::handleTabNameChanged(const QString &newName) {
    int index = -1;
    BaseTab *tab = qobject_cast<BaseTab *>(sender());
    // Modify parent window's title
    index = indexOf(tab);
    if (index >= 0) {
        setTabText(index, newName);
        emit titleChanged(index, newName);
    }
}
