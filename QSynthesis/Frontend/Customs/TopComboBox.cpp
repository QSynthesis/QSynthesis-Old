#include "TopComboBox.h"

TopComboBox::TopComboBox(QWidget *parent, const QStringList &list) : QWidget(parent) {
    setMinimumSize(600, 400); // can be modified
    lineEdit = new QLineEdit();
    listWidget = new QListWidget();
    listWidget->addItems(list);

    vlayout = new QVBoxLayout();
    vlayout->addWidget(lineEdit);
    vlayout->addWidget(listWidget);
    setLayout(vlayout);

    // this->setFocusPolicy(Qt::StrongFocus);

    lineEdit->setFocusPolicy(Qt::ClickFocus);
    listWidget->setFocusPolicy(Qt::ClickFocus);
    lineEdit->installEventFilter(this);
    listWidget->installEventFilter(this);

    connect(lineEdit, &QLineEdit::textChanged, [=](const QString &text) {
        auto fl = listWidget->findItems(text, Qt::MatchStartsWith);
        int cnt = listWidget->count();
        for (int i = 0; i < cnt; i++) {
            listWidget->item(i)->setHidden(true);
        }
        for (auto item : fl) {
            item->setHidden(false);
        }
        listWidget->setCurrentRow(0);
    });

    connect(listWidget, &QListWidget::itemActivated,
            [=](QListWidgetItem *item) { emit activated(indexFromItem(item)); });

    connect(listWidget, &QListWidget::currentRowChanged, this, &TopComboBox::currentIndexChanged);
    connect(listWidget, &QListWidget::currentTextChanged, this, &TopComboBox::currentTextChanged);
    connect(lineEdit, &QLineEdit::textChanged, this, &TopComboBox::editTextChanged);
    connect(listWidget, &QListWidget::itemEntered,
            [=](QListWidgetItem *item) { emit highlighted(indexFromItem(item)); });

    connect(listWidget, &QListWidget::itemActivated,
            [=](QListWidgetItem *item) { emit textActivated(item->text()); });

    connect(listWidget, &QListWidget::itemEntered,
            [=](QListWidgetItem *item) { emit textHighlighted(item->text()); });
}

int TopComboBox::indexFromItem(const QListWidgetItem *item) const {
    int cnt = listWidget->count();
    for (int i = 0; i < cnt; i++) {
        if (listWidget->item(i) == item)
            return i;
    }
    return -1;
}

QListWidgetItem *TopComboBox::itemFromIndex(int index) const {
    return listWidget->item(index);
}

bool TopComboBox::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        qDebug() << key;
        if ((key == Qt::Key_Up || key == Qt::Key_Down)) {
            if (obj == lineEdit) {
                listWidget->setFocus();
                QKeyEvent *newKeyEvent =
                    new QKeyEvent(QEvent::KeyPress, key, keyEvent->modifiers());
                QApplication::postEvent(listWidget, newKeyEvent);
                return true;
            }
        } else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
            qDebug() << "Select Over.";
        } else {
            if (obj == listWidget) {
                lineEdit->setFocus();
                QKeyEvent *newKeyEvent =
                    new QKeyEvent(QEvent::KeyPress, key, keyEvent->modifiers(), keyEvent->text());
                QApplication::postEvent(lineEdit, newKeyEvent);
                return true;
            }
        }
    }/* else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPoint p = this->mapFromGlobal(mouseEvent->pos());
        qDebug() << mouseEvent->pos() << this;
        if (!this->rect().contains(p)) {
            //   qDebug() << "Click Outside";
        }
    }*/
    return QWidget::eventFilter(obj, event);
}

void TopComboBox::setRoot(MainWindow *value)
{
    root = value;
}

void TopComboBox::addItem(const QString &text) {
    listWidget->addItem(text);
}

void TopComboBox::addItem(const QIcon &icon, const QString &text) {
    QListWidgetItem *item = new QListWidgetItem(icon, text);
    listWidget->addItem(item);
}

void TopComboBox::addItems(const QStringList &texts) {
    listWidget->addItems(texts);
}

int TopComboBox::count() const {
    return listWidget->count();
}

int TopComboBox::currentIndex() const {
    return listWidget->currentRow();
}

QString TopComboBox::currentText() const {
    return lineEdit->text();
}

int TopComboBox::findText(const QString &text, Qt::MatchFlags flags) const {
    return indexFromItem(listWidget->findItems(text, flags).first());
}

void TopComboBox::hidePopup() {
    listWidget->hide();
}

void TopComboBox::insertItem(int index, const QString &text) {
    listWidget->insertItem(index, text);
}
void TopComboBox::insertItem(int index, const QIcon &icon, const QString &text) {
    QListWidgetItem *item = new QListWidgetItem(icon, text);
    listWidget->insertItem(index, item);
}

void TopComboBox::insertItems(int index, const QStringList &list) {
    listWidget->insertItems(index, list);
}

QIcon TopComboBox::itemIcon(int index) const {
    return itemFromIndex(index)->icon();
}

QString TopComboBox::itemText(int index) const {
    return itemFromIndex(index)->text();
}

QString TopComboBox::placeholderText() const {
    return lineEdit->placeholderText();
}

void TopComboBox::removeItem(int index) {
    delete listWidget->takeItem(index);
}

void TopComboBox::setItemIcon(int index, const QIcon &icon) {
    itemFromIndex(index)->setIcon(icon);
}

void TopComboBox::setItemText(int index, const QString &text) {
    itemFromIndex(index)->setText(text);
}

void TopComboBox::setPlaceholderText(const QString &placeholderText) {
    lineEdit->setPlaceholderText(placeholderText);
}

void TopComboBox::showPopup() {
    listWidget->show();
}

void TopComboBox::clear() {
    listWidget->clear();
}

void TopComboBox::clearEditText() {
    lineEdit->clear();
}

void TopComboBox::setCurrentIndex(int index) {
    listWidget->setCurrentRow(index);
}

void TopComboBox::setCurrentText(const QString &text) {
    setEditText(text);
}
void TopComboBox::setEditText(const QString &text) {
    lineEdit->setText(text);
}
