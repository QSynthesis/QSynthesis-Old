#include "VectorButton.h"

VectorButton::VectorButton(QWidget *parent)
    : QLabel(parent), m_single(true), m_padding(QSize(0, 0)) {
    init();
}

VectorButton::VectorButton(bool single, QSizeF padding, QWidget *parent)
    : QLabel(parent), m_single(single), m_padding(padding) {
    init();
}

void VectorButton::setValues(bool single, QSizeF padding) {
    m_single = single;
    m_padding = padding;
}

void VectorButton::setIcons(QString on, QString off) {
    m_imgOn = on;
    if (!m_single) {
        m_imgOff = off;
    }
}

void VectorButton::setStatus(bool b) {
    if (m_single) {
        m_status = false;
    } else {
        m_status = b;
    }
    setIconCore();
}

bool VectorButton::status() const {
    return m_status;
}

QColor VectorButton::upColor() const {
    return m_upColor;
}

void VectorButton::setUpColor(const QColor &upColor) {
    m_upColor = upColor;
    reloadIcons();
    emit colorChanged();
}

QColor VectorButton::overColor() const {
    return m_overColor;
}

void VectorButton::setOverColor(const QColor &overColor) {
    m_overColor = overColor;
    reloadIcons();
    emit colorChanged();
}

QColor VectorButton::downColor() const {
    return m_downColor;
}

void VectorButton::setDownColor(const QColor &downColor) {
    m_downColor = downColor;
    reloadIcons();
    emit colorChanged();
}

void VectorButton::reloadIcons() {
    QSize size = this->size();
    if (size.width() < m_padding.width() || size.height() < m_padding.height()) {
        return;
    }

    QSize iconSize(size.width() - m_padding.width() * 2, size.height() - m_padding.height() * 2);

    // Create New
    bmpUp[0] = createBitmapFromSVG_W(m_imgOn, iconSize, m_upColor);
    bmpOver[0] = createBitmapFromSVG_W(m_imgOn, iconSize, m_overColor);
    bmpDown[0] = createBitmapFromSVG_W(m_imgOn, iconSize, m_downColor);

    if (!m_single) {
        bmpUp[1] = createBitmapFromSVG_W(m_imgOff, iconSize, m_upColor);
        bmpOver[1] = createBitmapFromSVG_W(m_imgOff, iconSize, m_overColor);
        bmpDown[1] = createBitmapFromSVG_W(m_imgOff, iconSize, m_downColor);
    }

    setIconCore();
}

void VectorButton::enterEvent(QEvent *event) {
    rollState = Qs::RollOver;
    setIconCore();
}

void VectorButton::leaveEvent(QEvent *event) {
    rollState = Qs::RollOut;
    setIconCore();
}

void VectorButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if (rollState == Qs::RollOut) {
        return;
    }
    rollState = Qs::RollDown;
    setIconCore();

    emit press();
}

void VectorButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }
    rollState = Qs::RollOver;
    setIconCore();

    emit clicked();
}

void VectorButton::resizeEvent(QResizeEvent *event) {
    reloadIcons();
}

void VectorButton::init() {
    setFocusPolicy(Qt::ClickFocus);

    m_status = false;
    rollState = Qs::RollOut;

    m_imgOn = m_imgOff = "";

    m_upColor = Qt::darkGray;
    m_overColor = Qt::lightGray;
    m_downColor = Qt::darkGray;
}

void VectorButton::setIconCore() {
    int index = m_status ? 1 : 0;

    if (m_single) {
        index = 0;
    }
    setAlignment(Qt::AlignCenter);
    if (rollState == 0) {
        setPixmap(bmpUp[index]);
    } else if (rollState == 1) {
        setPixmap(bmpOver[index]);
    } else {
        setPixmap(bmpDown[index]);
    }
}
