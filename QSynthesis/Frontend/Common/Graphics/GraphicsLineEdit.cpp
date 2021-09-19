#include "GraphicsLineEdit.h"
#include "AppAssistant.h"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QTextCursor>

GraphicsLineEdit::GraphicsLineEdit(QGraphicsItem *parent) : QGraphicsTextItem(parent) {
    initText();
}

GraphicsLineEdit::GraphicsLineEdit(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent) {
    initText();
}

void GraphicsLineEdit::initText() {
    // setTabChangesFocus(true);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    installEventFilter(this);

    recentText = text();
}
void GraphicsLineEdit::setText(const QString &text) {
    recentText = text;
    setPlainText(text);
}

QString GraphicsLineEdit::text() const {
    return toPlainText();
}

void GraphicsLineEdit::selectAll() {
    QTextDocument *doc = document();
    QTextCursor cursor(doc);
    cursor.select(QTextCursor::Document);
    setTextCursor(cursor);
}

void GraphicsLineEdit::moveCursorToEnd() {
    QTextDocument *doc = document();
    QTextCursor cursor(doc);
    cursor.movePosition(QTextCursor::End);
    setTextCursor(cursor);
}

bool GraphicsLineEdit::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this) {
        if (AppAssistant::keyIsDown(event)) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            int key = keyEvent->key();
            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                qDebug() << "Enter";
                onEditingFinished();
                return true;
            }
        }
    }
    return QGraphicsTextItem::eventFilter(obj, event);
}

void GraphicsLineEdit::focusOutEvent(QFocusEvent *event) {
    QGraphicsTextItem::focusOutEvent(event);
    emit loseFocus();
    onEditingFinished();
}

void GraphicsLineEdit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
    painter->setBrush(Qt::white);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());

    QGraphicsTextItem::paint(painter, option, widget);
}

void GraphicsLineEdit::onEditingFinished() {
    if (hasFocus()) {
        clearFocus();
    }
    QString currentText = text();
    if (currentText == recentText) {
        return;
    }
    recentText = currentText;
    emit editingFinished2();
}
