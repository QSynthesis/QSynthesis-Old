#include "IconButton.h"

#include <QStyle>

IconButton::IconButton(QWidget *parent) : QLabel(parent), m_padding(QSize(0, 0)) {
    init();
}

IconButton::IconButton(QSizeF padding, QWidget *parent) : QLabel(parent), m_padding(padding) {
    init();
}

void IconButton::init() {
    setFocusPolicy(Qt::ClickFocus);

    rollState = Qs::RollOut;

    m_path = "";

    m_upColor = Qt::transparent;
    m_overColor = QColor(0, 0, 0, 32);
    m_downColor = QColor(0, 0, 0, 64);
    m_iconColor = QColor(0x333333);

    m_radius = 5;
}

void IconButton::setPadding(QSizeF padding) {
    m_padding = padding;
}

QSizeF IconButton::padding() const {
    return m_padding;
}

void IconButton::setIcon(const QString &path) {
    m_path = path;
}

QColor IconButton::upColor() const {
    return m_upColor;
}

void IconButton::setUpColor(const QColor &upColor) {
    m_upColor = upColor;
    emit colorChanged();
}

QColor IconButton::overColor() const {
    return m_overColor;
}

void IconButton::setOverColor(const QColor &overColor) {
    m_overColor = overColor;
    emit colorChanged();
}

QColor IconButton::downColor() const {
    return m_downColor;
}

void IconButton::setDownColor(const QColor &downColor) {
    m_downColor = downColor;
    emit colorChanged();
}

QColor IconButton::iconColor() const {
    return m_iconColor;
}

void IconButton::setIconColor(const QColor &iconColor) {
    m_iconColor = iconColor;
    reloadIcons();
    emit colorChanged();
}

void IconButton::reloadIcons() {
    QSize size = this->size();
    if (size.width() < m_padding.width() || size.height() < m_padding.height()) {
        return;
    }

    QSize iconSize(size.width() - m_padding.width() * 2, size.height() - m_padding.height() * 2);

    m_bmp = createBitmapFromSVG_W(m_path, iconSize, m_iconColor);

    setAlignment(Qt::AlignCenter);
    setPixmap(m_bmp);
}

void IconButton::setRollState(Qs::ButtonStatus state) {
    rollState = state;
    update();
}

void IconButton::enterEvent(QEvent *event) {
    setRollState(Qs::RollOver);
}

void IconButton::leaveEvent(QEvent *event) {
    setRollState(Qs::RollOut);
}

void IconButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }
    if (rollState == Qs::RollOut) {
        return;
    }
    setRollState(Qs::RollDown);

    emit press();
}

void IconButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }
    setRollState(Qs::RollOver);

    if (rect().contains(event->pos())) {
        emit clicked();
    }
}

void IconButton::resizeEvent(QResizeEvent *event) {
    reloadIcons();
}

void IconButton::paintEvent(QPaintEvent *event) {
    QRect rect = this->rect();
    rect.adjust(1, 1, -1, -1);

    QColor color;
    if (rollState == Qs::RollOver) {
        color = m_overColor;
    } else if (rollState == Qs::RollDown) {
        color = m_downColor;
    } else {
        color = m_upColor;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(color));
    painter.drawRoundedRect(rect, m_radius, m_radius);

    QLabel::paintEvent(event);
}

double IconButton::radius() const {
    return m_radius;
}

void IconButton::setRadius(double radius) {
    m_radius = radius;
    update();
    emit radiusChanged();
}
