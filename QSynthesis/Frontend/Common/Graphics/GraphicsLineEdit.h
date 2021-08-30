#ifndef GRAPHICSLINEEDIT_H
#define GRAPHICSLINEEDIT_H

#include <QDebug>
#include <QGraphicsTextItem>

class GraphicsLineEdit : public QGraphicsTextItem {
    Q_OBJECT
public:
    GraphicsLineEdit(QGraphicsItem *parent = nullptr);
    GraphicsLineEdit(const QString &text, QGraphicsItem *parent = nullptr);

    void setText(const QString &text);
    QString text() const;

    void selectAll();
    void moveCursorToEnd();

private:
    QString recentText;

    bool eventFilter(QObject *obj, QEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    void initText();
    void onEditingFinished();

signals:
    void editingFinished2();
    void loseFocus();
};

#endif // GRAPHICSLINEEDIT_H
