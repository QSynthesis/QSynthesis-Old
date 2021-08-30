#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QStringList>
#include <QWidget>

#include "QUtils.h"

class TopComboBox : public QWidget {
    Q_OBJECT
public:
    QLineEdit *lineEdit;
    QListWidget *listWidget;

    explicit TopComboBox(QWidget *parent = nullptr, const QStringList &list = QStringList());

    void addItem(const QString &text);
    void addItem(const QIcon &icon, const QString &text);
    void addItems(const QStringList &texts);
    int count() const;
    int currentIndex() const;
    QString currentText() const;
    int findText(const QString &text,
                 Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchCaseSensitive) const;
    virtual void hidePopup();
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

    void setRoot(MainWindow *value);

protected:
    int indexFromItem(const QListWidgetItem *item) const;
    QListWidgetItem *itemFromIndex(int index) const;

    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QVBoxLayout *vlayout;

    MainWindow *root;

signals:
    void activated(int index);
    void currentIndexChanged(int index);
    void currentTextChanged(const QString &text);
    void editTextChanged(const QString &text);
    void highlighted(int index);
    void textActivated(const QString &text);
    void textHighlighted(const QString &text);
};

#endif // COMBOBOX_H
