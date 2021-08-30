#include "TemporaryMenu.h"

TemporaryMenu::TemporaryMenu(QWidget *parent) : QMenu(parent) {
}

TemporaryMenu::TemporaryMenu(const QStringList &list, QWidget *parent)
    : QMenu(parent), m_texts(list) {
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

void TemporaryMenu::clearTexts() {
    m_texts.clear();
}

void TemporaryMenu::prepare() {
    int i = 0;
    for (auto it = m_texts.begin(); it != m_texts.end(); ++it, ++i) {
        QAction *action = new QAction(*it, this);
        action->setData(i);
        addAction(action);
    }
}
