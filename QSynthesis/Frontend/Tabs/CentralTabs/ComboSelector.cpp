#include "ComboSelector.h"

ComboSelector::ComboSelector(QWidget *parent, const QStringList &list) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);

    lineEdit = new QLineEdit();
    listWidget = new QListWidget();
    listWidget->addItems(list);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(lineEdit);
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);

    lineEdit->setFocusPolicy(Qt::ClickFocus);
    listWidget->setFocusPolicy(Qt::ClickFocus);
    lineEdit->installEventFilter(this);
    listWidget->installEventFilter(this);

    connect(lineEdit, &QLineEdit::textChanged, this, &ComboSelector::handleTextChanged);

    connect(listWidget, &QListWidget::currentRowChanged, this,
            &ComboSelector::handleCurrentRowChanged);
    connect(listWidget, &QListWidget::currentTextChanged, this,
            &ComboSelector::handleCurrentTextChanged);
    connect(listWidget, &QListWidget::itemClicked, this, &ComboSelector::handleItemClicked);
}

ComboSelector::~ComboSelector() {
}

int ComboSelector::indexOf(const QListWidgetItem *item) const {
    int cnt = listWidget->count();
    for (int i = 0; i < cnt; i++) {
        if (listWidget->item(i) == item) {
            return i;
        }
    }
    return -1;
}

QListWidgetItem *ComboSelector::itemOf(int index) const {
    return listWidget->item(index);
}

int ComboSelector::activeIndexOf(const QListWidgetItem *item) const {
    int count = listWidget->count();
    int num = 0;
    for (int i = 0; i < count; i++) {
        QListWidgetItem *cur = listWidget->item(i);
        if (cur->isHidden()) {
            continue;
        }
        if (cur == item) {
            return num;
        }
        num++;
    }
    return -1;
}

QListWidgetItem *ComboSelector::activeItemOf(int index) const {
    int count = listWidget->count();
    int num = 0;
    for (int i = 0; i < count; i++) {
        QListWidgetItem *cur = listWidget->item(i);
        if (cur->isHidden()) {
            continue;
        }
        if (num == index) {
            return cur;
        }
        num++;
    }
    return nullptr;
}

bool ComboSelector::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if ((key == Qt::Key_Up || key == Qt::Key_Down)) {
            if (obj == lineEdit) {
                listWidget->setFocus();
                QKeyEvent *newKeyEvent =
                    new QKeyEvent(QEvent::KeyPress, key, keyEvent->modifiers());
                QApplication::postEvent(listWidget, newKeyEvent);
                return true;
            }
        } else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
            int index = currentIndex();
            if (index >= 0 && index < listWidget->count()) {
                emit activated(index);
            }
            return true;
        } else if (key == Qt::Key_Escape) {
            emit abandoned();
            return true;
        } else {
            if (obj == listWidget) {
                lineEdit->setFocus();
                QKeyEvent *newKeyEvent =
                    new QKeyEvent(QEvent::KeyPress, key, keyEvent->modifiers(), keyEvent->text());
                QApplication::postEvent(lineEdit, newKeyEvent);
                return true;
            }
        }
    } else if (event->type() == QEvent::FocusOut) {
        if (!lineEdit->hasFocus() && !listWidget->hasFocus()) {
            emit abandoned();
        }
    }
    return QWidget::eventFilter(obj, event);
}

QString ComboSelector::clues() const {
    return lineEdit->placeholderText();
}

void ComboSelector::setClues(const QString &clues) {
    lineEdit->setPlaceholderText(clues);
}

void ComboSelector::handleTextChanged(const QString &text) {
    QList<QListWidgetItem *> items = listWidget->findItems(text, Qt::MatchContains);
    int cnt = listWidget->count();
    for (int i = 0; i < cnt; i++) {
        listWidget->item(i)->setHidden(true);
    }
    for (QListWidgetItem *item : items) {
        item->setHidden(false);
    }

    int index = indexOf(activeItemOf(0));
    if (index >= 0 && index < listWidget->count()) {
        listWidget->setCurrentRow(index);
    }
    emit editTextChanged(text);
}

void ComboSelector::handleCurrentRowChanged(int row) {
    emit currentIndexChanged(row);
}

void ComboSelector::handleCurrentTextChanged(const QString &text) {
    emit currentTextChanged(text);
}

void ComboSelector::handleItemClicked(QListWidgetItem *item) {
    emit activated(indexOf(item));
}

void ComboSelector::addItem(const QString &text) {
    listWidget->addItem(text);
}

void ComboSelector::addItem(const QIcon &icon, const QString &text) {
    QListWidgetItem *item = new QListWidgetItem(icon, text);
    listWidget->addItem(item);
}

void ComboSelector::addItems(const QStringList &texts) {
    listWidget->addItems(texts);
}

void ComboSelector::setItems(const QStringList &texts) {
    listWidget->clear();
    listWidget->addItems(texts);
}

int ComboSelector::count() const {
    return listWidget->count();
}

int ComboSelector::currentIndex() const {
    return listWidget->currentRow();
}

QString ComboSelector::currentText() const {
    return lineEdit->text();
}

int ComboSelector::findText(const QString &text, Qt::MatchFlags flags) const {
    return indexOf(listWidget->findItems(text, flags).first());
}

void ComboSelector::insertItem(int index, const QString &text) {
    listWidget->insertItem(index, text);
}
void ComboSelector::insertItem(int index, const QIcon &icon, const QString &text) {
    QListWidgetItem *item = new QListWidgetItem(icon, text);
    listWidget->insertItem(index, item);
}

void ComboSelector::insertItems(int index, const QStringList &list) {
    listWidget->insertItems(index, list);
}

QIcon ComboSelector::itemIcon(int index) const {
    return itemOf(index)->icon();
}

QString ComboSelector::itemText(int index) const {
    return itemOf(index)->text();
}

QString ComboSelector::placeholderText() const {
    return lineEdit->placeholderText();
}

void ComboSelector::removeItem(int index) {
    delete listWidget->takeItem(index);
}

void ComboSelector::setItemIcon(int index, const QIcon &icon) {
    itemOf(index)->setIcon(icon);
}

void ComboSelector::setItemText(int index, const QString &text) {
    itemOf(index)->setText(text);
}

void ComboSelector::setPlaceholderText(const QString &placeholderText) {
    lineEdit->setPlaceholderText(placeholderText);
}

void ComboSelector::showPopup() {
    listWidget->show();
}

void ComboSelector::clear() {
    listWidget->clear();
}

void ComboSelector::clearEditText() {
    lineEdit->clear();
}

void ComboSelector::setCurrentIndex(int index) {
    listWidget->setCurrentRow(index);
}

void ComboSelector::setCurrentText(const QString &text) {
    setEditText(text);
}

void ComboSelector::setEditText(const QString &text) {
    lineEdit->setText(text);
}

void ComboSelector::setVisible(bool visible) {
    QWidget::setVisible(visible);
    if (visible) {
        lineEdit->setFocus();
    }
    emit visibilityChanged(visible);
}
