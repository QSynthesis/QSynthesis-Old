#ifndef FIXEDCOMBOBOX_H
#define FIXEDCOMBOBOX_H

#include <QComboBox>

class FixedComboBox : public QComboBox {
    Q_OBJECT
public:
    explicit FixedComboBox(QWidget *parent = nullptr);
    ~FixedComboBox();
};

#endif // FIXEDCOMBOBOX_H
