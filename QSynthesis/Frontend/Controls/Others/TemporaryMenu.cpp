#include "TemporaryMenu.h"

TemporaryMenu::TemporaryMenu(QWidget *parent) : QMenu(parent) {
    m_checkable = false;
}

TemporaryMenu::TemporaryMenu(const QStringList &list,QWidget *parent)
    : QMenu(parent), m_texts(list) {
    m_checkable = false;
}

TemporaryMenu::~TemporaryMenu() {
}

int TemporaryMenu::start() {
    return start(QCursor::pos());
}

int TemporaryMenu::start(QPoint pos) {
    prepare();

    QAction *action = exec(pos);
    int data = -1;
    if (action) {
        data = action->data().toInt();
    }
    clear();

    return data;
}

QStringList TemporaryMenu::texts() const {
    return m_texts;
}

void TemporaryMenu::setTexts(const QStringList &texts) {
    m_texts = texts;
}

void TemporaryMenu::setCheckedAt(int index, bool checked) {
    m_checks.insert(index, checked);
}

void TemporaryMenu::setVisibleAt(int index, bool visible) {
    m_visibilities.insert(index, visible);
}

void TemporaryMenu::setEnabledAt(int index, bool enabled) {
    m_enables.insert(index, enabled);
}

bool TemporaryMenu::checkable() const {
    return m_checkable;
}

void TemporaryMenu::setCheckable(bool checkable) {
    m_checkable = checkable;
}

void TemporaryMenu::clearContents() {
    m_texts.clear();
    m_checks.clear();
    m_enables.clear();
    m_visibilities.clear();
}

void TemporaryMenu::prepare() {
    int i = 0;
    for (auto it = m_texts.begin(); it != m_texts.end(); ++it) {
        if (it->isEmpty()) {
            addSeparator();
        } else {
            QAction *action = new QAction(*it, this);
            action->setData(i);

            if (m_checkable) {
                action->setCheckable(true);
            }

            auto it1 = m_checks.find(i);
            if (it1 != m_checks.end()) {
                action->setCheckable(true);
                action->setChecked(it1.value());
            }

            auto it2 = m_enables.find(i);
            if (it2 != m_enables.end()) {
                action->setEnabled(it2.value());
            }

            auto it3 = m_visibilities.find(i);
            if (it3 != m_visibilities.end()) {
                action->setVisible(it3.value());
            }

            addAction(action);
            i++;
        }
    }
}
