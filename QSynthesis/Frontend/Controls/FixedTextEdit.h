#ifndef FIXEDTEXTEDIT_H
#define FIXEDTEXTEDIT_H

#include <QDebug>
#include <QPlainTextEdit>

class FixedTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    FixedTextEdit(QWidget *parent = nullptr);
    FixedTextEdit(const QString &text, QWidget *parent = nullptr);

    void setText(const QString &text);
    QString text() const;

private:
    QString recentText;

    bool eventFilter(QObject *obj, QEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void initText();
    void onEditingFinished();

signals:
    void editingFinished2();
    void loseFocus();
};

#endif // FIXEDTEXTEDIT_H
