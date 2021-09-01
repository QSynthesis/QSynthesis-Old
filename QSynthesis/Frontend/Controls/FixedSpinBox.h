#ifndef FIXEDSPINBOX_H
#define FIXEDSPINBOX_H

#include <QDoubleSpinBox>

class FixedSpinBox : public QDoubleSpinBox {
    Q_OBJECT
public:
    explicit FixedSpinBox(QWidget *parent = nullptr);
    ~FixedSpinBox();
};

#endif // FIXEDSPINBOX_H
