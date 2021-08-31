#include "ComboControl.h"

/*--------------------------------------列表框控制--------------------------------------*/
ComboControl::ComboControl(Qt::Orientation orient, QWidget *parent)
    : QWidget(parent), orient(orient) {
    QStringList a{};
    InitComboControl("", a);
}

ComboControl::ComboControl(Qt::Orientation orient, QString text, QWidget *parent)
    : QWidget(parent), orient(orient) {
    QStringList a{};
    InitComboControl(text, a);
}

ComboControl::ComboControl(Qt::Orientation orient, QString text, const QStringList &values,
                           QWidget *parent)
    : QWidget(parent), orient(orient) {
    InitComboControl(text, values);
}

void ComboControl::setCaption(QString caption) {
    pLabel->setText(caption);
    pLabel->adjustSize();
}

QString ComboControl::caption() const {
    return pLabel->text();
}

void ComboControl::setProportion(int a, int b) {
    if (orient == Qt::Horizontal) {
        QHBoxLayout *layout = qobject_cast<QHBoxLayout *>(pLayout);
        layout->setStretchFactor(pLabel, a);
        layout->setStretchFactor(pCombo, b);
    } else {
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(pLayout);
        layout->setStretchFactor(pLabel, a);
        layout->setStretchFactor(pCombo, b);
    }
}

void ComboControl::setMargin(int n) {
    pLayout->setMargin(n);
}

void ComboControl::setUnmodified(bool value) {
    if (value) {
        pCombo->setStyleSheet("background-color:#E1E1E1;");
    } else {
        pCombo->setStyleSheet("background-color:white;");
    }
    bUnmodified = value;
}

bool ComboControl::isUnmodified() {
    return bUnmodified;
}

QComboBox *ComboControl::Combo() const {
    return pCombo;
}

void ComboControl::InitComboControl(QString text, const QStringList &values) {

    pLabel = new QLabel(text, this);
    pCombo = new QComboBox(this);

    pLabel->adjustSize();
    pCombo->adjustSize();

    if (orient == Qt::Horizontal) {
        pLayout = new QHBoxLayout(this);
    } else {
        pLayout = new QVBoxLayout(this);
    }

    pLayout->setMargin(0);

    pLayout->addWidget(pLabel);
    pLayout->addWidget(pCombo);

    if (!values.empty()) {
        pCombo->addItems(values);
    }

    setLayout(pLayout);

    connect(pCombo, &QComboBox::currentTextChanged, this, &ComboControl::onModifyAction);
    bUnmodified = false;
}

void ComboControl::onModifyAction() {
    if (bUnmodified) {
        setUnmodified(false);
    }
}

Qt::Orientation ComboControl::orientation() const {
    return orient;
}
