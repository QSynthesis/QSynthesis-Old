#include "FormTitleBar.h"
#include "../BaseForm.h"

FormTitleBar::FormTitleBar(BaseForm *parent) : MoreWidget(parent), parentForm(parent) {
    initializeComponents(30, 1);
}

FormTitleBar::FormTitleBar(int h, BaseForm *parent) : MoreWidget(parent), parentForm(parent) {
    initializeComponents(h, 1);
}

int FormTitleBar::contentHeight() const {
    return m_height;
}

void FormTitleBar::setContentHeight(int h) {
    m_height = h;
    setFixedHeight(m_top + m_height);
    update();
}

int FormTitleBar::top() const {
    return m_top;
}

void FormTitleBar::setTop(double t) {
    m_top = t;
    itemsLayout->setContentsMargins(15, t, 15, 0);
    setFixedHeight(m_top + m_height);
    update();

    emit topChanged();
}

void FormTitleBar::setTopVisible(bool value) {
    topVisible = value;
    update();

    emit contentHeightChanged();
}

void FormTitleBar::addItem(QWidget *item, bool rightToLeft, bool hidden, bool showen) {
    int index = itemsLayout->indexOf(stretch) + rightToLeft;
    itemsLayout->insertWidget(index, item);
    itemsList.append(titleBarItem(item, hidden, showen));

    if (!showen) {
        item->hide();
    }
}

void FormTitleBar::removeItem(QWidget *item) {
    for (int i = 0; i != itemsList.size(); ++i) {
        if (itemsList.at(i).item == item) {
            itemsLayout->removeWidget(item);
            itemsList.removeAt(i);
            break;
        }
    }
}

void FormTitleBar::hideItems() {
    setItemsVisible(false);
}

void FormTitleBar::showItems() {
    setItemsVisible(true);
}

void FormTitleBar::setItemsVisible(bool value) {
    for (int i = 0; i != itemsList.size(); ++i) {
        titleBarItem item = itemsList.at(i);
        QWidget *p = item.item;
        if (item.hidden && !value) {
            p->setVisible(value);
        } else if (item.showen && value) {
            p->setVisible(value);
        }
    }
}

QColor FormTitleBar::topColor() const {
    return m_topColor;
}

void FormTitleBar::setTopColor(const QColor &value) {
    m_topColor = value;
    update();

    emit colorChanged();
}

QColor FormTitleBar::fillColor() const {
    return m_fillColor;
}

void FormTitleBar::setFillColor(const QColor &value) {
    m_fillColor = value;
    update();

    emit colorChanged();
}

void FormTitleBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect rect = this->rect();

    painter.setClipRegion(event->region());
    painter.setPen(Qt::transparent);

    if (topVisible) {
        painter.setBrush(QBrush(m_topColor, Qt::SolidPattern));
    } else {
        painter.setBrush(QBrush(m_fillColor, Qt::SolidPattern));
    }
    painter.drawRect(rect.left(), rect.top(), rect.width(), m_top);

    painter.setBrush(QBrush(m_fillColor, Qt::SolidPattern));
    painter.drawRect(rect.left(), rect.top() + m_top, rect.width(), rect.height() - m_top);
}

// 初始化标题栏
void FormTitleBar::initializeComponents(int h, int t) {
    m_topColor = Qt::lightGray;
    m_fillColor = Qt::white;

    m_height = h;
    m_top = t;

    topVisible = true;

    itemsLayout = new QHBoxLayout(this);
    itemsLayout->setContentsMargins(15, t, 15, 0);
    itemsLayout->setSpacing(20);
    setLayout(itemsLayout);

    itemsLayout->addStretch(); // First Stretching
    stretch = itemsLayout->itemAt(0);

    setFixedHeight(m_top + m_height);
}
