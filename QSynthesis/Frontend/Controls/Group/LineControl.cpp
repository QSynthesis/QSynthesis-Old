#include "LineControl.h"

#include <QStyle>

/*--------------------------------------文本控制--------------------------------------*/
LineControl::LineControl(Qt::Orientation orient,QWidget *parent)
    :QWidget(parent), orient(orient) {
    InitLineControl("", "");
}

LineControl::LineControl(Qt::Orientation orient, QString text,QWidget *parent)
    :QWidget(parent), orient(orient) {
    InitLineControl(text, "");
}

LineControl::LineControl(Qt::Orientation orient, QString text, QString value,QWidget *parent)
    :QWidget(parent), orient(orient) {
    InitLineControl(text, value);
}

void LineControl::setBlankValue(double value) {
    blankValue = value;
}

void LineControl::setCaption(QString caption) {
    pLabel->setText(caption);
    pLabel->adjustSize();
}

void LineControl::setProportion(int a, int b) {
    if (orient == Qt::Horizontal) {
        QHBoxLayout *layout = qobject_cast<QHBoxLayout *>(pLayout);
        layout->setStretchFactor(pLabel, a);
        layout->setStretchFactor(pText, b);
    } else {
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(pLayout);
        layout->setStretchFactor(pLabel, a);
        layout->setStretchFactor(pText, b);
    }
}

void LineControl::setMargin(int n) {
    pLayout->setMargin(n);
}

void LineControl::setSpacing(int n) {
    pLayout->setMargin(n);
}

void LineControl::setUnmodified(bool value) {
    if (value) {
        pText->setProperty("status", "unmodified");
        style()->polish(pText);
        pText->setPlaceholderText(placeholderUnmodified);
    } else {
        pText->setProperty("status", "normal");
        style()->polish(pText);
        pText->setPlaceholderText(placeholderModified);
    }
    m_unmodified = value;
}

bool LineControl::unmodified() const {
    return m_unmodified;
}

void LineControl::setPlaceholder(QString modi, QString unmo) {
    placeholderModified = modi;
    placeholderUnmodified = unmo;
    if (m_unmodified) {
        pText->setPlaceholderText(unmo);
    } else {
        pText->setPlaceholderText(modi);
    }
}

void LineControl::setValue(QString value) {
    pText->setText(value);
}

QString LineControl::getValue() const {
    return pText->text();
}

FixedLineEdit *LineControl::Text() const {
    return pText;
}

void LineControl::InitLineControl(QString text, QString value) {
    pLabel = new QLabel(text, this);

    pText = new FixedLineEdit(value, this);
    pText->setProperty("status", "normal");

    pValidator = nullptr;

    pLabel->adjustSize();
    pText->adjustSize();

    setBlankValue(0);

    if (orient == Qt::Horizontal) {
        pLayout = new QHBoxLayout(this);
    } else {
        pLayout = new QVBoxLayout(this);
    }
    pLayout->setMargin(0);

    pLayout->addWidget(pLabel);
    pLayout->addWidget(pText);

    setLayout(pLayout);

    connect(pText, &FixedLineEdit::textChanged, this, &LineControl::onTextChanged);

    pText->setPlaceholderText(placeholderModified);
    m_unmodified = false;
}

void LineControl::onModifyAction() {
    if (m_unmodified) {
        bool status = pText->isClearButtonEnabled();
        pText->setClearButtonEnabled(false);
        pText->clear();
        pText->setClearButtonEnabled(status);

        setUnmodified(false);
    }
}

void LineControl::onTextChanged(QString s) {
    onModifyAction();

    QDoubleValidator *dblV = qobject_cast<QDoubleValidator *>(pValidator);
    QIntValidator *intV = qobject_cast<QIntValidator *>(pValidator);

    if (dblV) {
        double n = (s.isEmpty() || !isNumber(s, true, true)) ? dblV->bottom() : s.toDouble();

        if (n > dblV->top()) {
            n = dblV->top();
            s = QString::number(n);
            pText->setText(s);
        }
    } else if (intV) {
        int n = (s.isEmpty() || !isNumber(s, true, true)) ? intV->bottom() : s.toDouble();

        if (n > intV->top()) {
            n = intV->top();
            s = QString::number(n);
            pText->setText(s);
        }
    }
}

void LineControl::setValidator(QValidator *v) {
    pValidator = v;
    pText->setValidator(v);
}

Qt::Orientation LineControl::orientation() const {
    return orient;
}

void LineControl::moveCursorToEnd() {
    pText->setCursorPosition(pText->text().size());
}
