#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QStringList>
#include <QWidget>

#include "Widgets/TransparentContainer.h"
#include "Controls/Inputs/FixedLineEdit.h"
#include "Macros.h"

#define qSelector ComboSelector::instance()

class ComboSelector : public TransparentContainer {
    Q_OBJECT
    Q_SINGLETON(ComboSelector)

public:
    explicit ComboSelector(QWidget *parent = nullptr, const QStringList &list = {});
    virtual ~ComboSelector();

    void addItem(const QString &text);
    void addItem(const QIcon &icon, const QString &text);
    void addItems(const QStringList &texts);

    void setItems(const QStringList &texts);

    int count() const;
    int currentIndex() const;
    QString currentText() const;
    int findText(const QString &text,
                 Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchCaseSensitive) const;
    void insertItem(int index, const QString &text);
    void insertItem(int index, const QIcon &icon, const QString &text);
    void insertItems(int index, const QStringList &list);
    QIcon itemIcon(int index) const;
    QString itemText(int index) const;
    QString placeholderText() const;
    void removeItem(int index);
    void setItemIcon(int index, const QIcon &icon);
    void setItemText(int index, const QString &text);
    void setPlaceholderText(const QString &placeholderText);
    virtual void showPopup();
    void clear();
    void clearEditText();
    void setCurrentIndex(int index);
    void setCurrentText(const QString &text);
    void setEditText(const QString &text);

    void setVisible(bool visible) override;

    void activate(int index);
    void abandon();

public:
    QString clues() const;
    void setClues(const QString &clues);

protected:
    int indexOf(const QListWidgetItem *item) const;
    QListWidgetItem *itemOf(int index) const;

    int activeIndexOf(const QListWidgetItem *item) const;
    QListWidgetItem *activeItemOf(int index) const;

    void focusInEvent(QFocusEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    void handleGlobalMouseClicked(QMouseEvent *event);

private:
    QVBoxLayout *mainLayout;
    FixedLineEdit *lineEdit;
    QListWidget *listWidget;

    void handleTextChanged(const QString &text);
    void handleCurrentRowChanged(int row);
    void handleCurrentTextChanged(const QString &text);
    void handleItemClicked(QListWidgetItem *item);

signals:
    void activated(int index);
    void abandoned();

    void currentIndexChanged(int index);
    void currentTextChanged(const QString &text);
    void editTextChanged(const QString &text);
    void highlighted(int index);
    void textActivated(const QString &text);
    void textHighlighted(const QString &text);

    void visibilityChanged(bool visibility);
};

#endif // COMBOBOX_H
