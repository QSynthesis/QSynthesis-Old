#include "MoreWidget.h"

MoreWidget::MoreWidget(QWidget *parent) :QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setFocusPolicy(Qt::ClickFocus);
}

MoreWidget::~MoreWidget() {
}
