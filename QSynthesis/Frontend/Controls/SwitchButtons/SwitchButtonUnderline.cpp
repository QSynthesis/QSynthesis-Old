#include "SwitchButtonUnderline.h"
#include "../SwitchButton.h"
#include "SwitchButtonGroup.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

SwitchButtonUnderline::SwitchButtonUnderline(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_group = nullptr;
    m_btn = nullptr;

    m_leftAnimation = new QPropertyAnimation(this, "left");
    m_rightAnimation = new QPropertyAnimation(this, "right");

    m_leftAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_rightAnimation->setEasingCurve(QEasingCurve::OutCubic);

    setTweenDuration(200);
    setColor(Qt::white);
    setLineWidth(10);
}

SwitchButtonUnderline::~SwitchButtonUnderline() {
}

SwitchButtonGroup *SwitchButtonUnderline::group() const {
    return m_group;
}

void SwitchButtonUnderline::setGroup(SwitchButtonGroup *group) {
    removeGroup();
    m_group = group;
    connect(m_group, &SwitchButtonGroup::switched, this, &SwitchButtonUnderline::handleSwitched);
}

void SwitchButtonUnderline::removeGroup() {
    if (m_group) {
        disconnect(m_group, &SwitchButtonGroup::switched, this,
                   &SwitchButtonUnderline::handleSwitched);
        m_group = nullptr;
    }
}

int SwitchButtonUnderline::tweenDuration() const {
    return m_leftAnimation->duration();
}

void SwitchButtonUnderline::setTweenDuration(int duration) {
    m_leftAnimation->setDuration(duration);
    m_rightAnimation->setDuration(duration);
}

int SwitchButtonUnderline::left() const {
    return m_left;
}

void SwitchButtonUnderline::setLeft(int left) {
    m_left = left;
    update();

    emit leftChanged();
}

int SwitchButtonUnderline::right() const {
    return m_right;
}

void SwitchButtonUnderline::setRight(int right) {
    m_right = right;
    update();

    emit rightChanged();
}

QColor SwitchButtonUnderline::color() const {
    return m_color;
}

void SwitchButtonUnderline::setColor(const QColor &color) {
    m_color = color;
    update();

    emit colorChanged();
}

void SwitchButtonUnderline::setRealtimeState() {
    m_leftAnimation->stop();
    m_rightAnimation->stop();

    QPair<int, int> target = getTarget(m_btn);
    m_left = target.first;
    m_right = target.second;

    update();
}

int SwitchButtonUnderline::lineWidth() const {
    return height();
}

void SwitchButtonUnderline::setLineWidth(int lineWidth) {
    setFixedHeight(lineWidth);
    emit lineWidthChanged();
}

QPair<int, int> SwitchButtonUnderline::getTarget(SwitchButton *btn) const {
    QPoint pos =
        mapFromParent(parentWidget()->mapFromGlobal(btn->parentWidget()->mapToGlobal(btn->pos())));
    return qMakePair(pos.x(), pos.x() + btn->width());
}

void SwitchButtonUnderline::runAnimation() {
    QPair<int, int> target = getTarget(m_btn);

    QPropertyAnimation *a = m_leftAnimation;
    a->stop();
    a->setStartValue(m_left);
    a->setEndValue(target.first);

    QPropertyAnimation *b = m_rightAnimation;
    b->stop();
    b->setStartValue(m_right);
    b->setEndValue(target.second);

    a->start();
    b->start();
}

void SwitchButtonUnderline::setButton(SwitchButton *btn) {
    if (m_btn) {
        m_btn->removeEventFilter(this);
    }
    m_btn = btn;
    m_btn->installEventFilter(this);
}

void SwitchButtonUnderline::handleSwitched() {
    setButton(m_group->currentButton());
    runAnimation();
}

void SwitchButtonUnderline::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));
    painter.drawRect(QRect(m_left, 0, m_right - m_left, height()));
}

bool SwitchButtonUnderline::eventFilter(QObject *obj, QEvent *event) {
    if (obj == m_btn) {
        if (event->type() == QEvent::Move) {
            QMoveEvent *moveEvent = static_cast<QMoveEvent *>(event);
            if (moveEvent->oldPos().x() != moveEvent->pos().x()) {
                setRealtimeState();
            }
        } else if (event->type() == QEvent::Resize) {
            QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(event);
            if (resizeEvent->oldSize().width() != resizeEvent->size().width()) {
                setRealtimeState();
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
