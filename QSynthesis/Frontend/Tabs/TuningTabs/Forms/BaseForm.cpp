#include "BaseForm.h"

BaseForm::BaseForm(QWidget *parent) : QWidget(parent) {
    m_unfolded = true;
    m_widget = nullptr;
    m_titleBar = nullptr;
}

BaseForm::BaseForm(QWidget *w, FormTitleBar *bar, QWidget *parent) : QWidget(parent) {
    m_unfolded = true;
    m_titleBar = bar;
    m_widget = w;

    init();
}

QWidget *BaseForm::widget() const {
    return m_widget;
}

void BaseForm::setWidget(QWidget *w) {
    if (m_widget) {
        return;
    }

    m_widget = w;

    if (m_titleBar && m_widget) {
        init();
    }
}

void BaseForm::setDefaultWidget() {
    setWidget(new QWidget(this));
}

FormTitleBar *BaseForm::titleBar() const {
    return m_titleBar;
}

void BaseForm::setTitleBar(FormTitleBar *bar) {
    if (m_titleBar) {
        return;
    }
    m_titleBar = bar;
    if (m_titleBar && m_widget) {
        init();
    }
}

void BaseForm::setDefaultTitleBar() {
    setTitleBar(new FormTitleBar(this));
}

bool BaseForm::unfolded() const {
    return m_unfolded;
}

void BaseForm::setUnfolded(bool value) {
    m_unfolded = value;
    m_widget->setVisible(value);
    m_titleBar->setItemsVisible(value);

    if (value) {
        setMaximumHeight(10000);
    } else {
        setMaximumHeight(m_titleBar->height());
    }
    adjustSize();

    emit visibilityChanged(value);
}

void BaseForm::reverseFold() {
    setUnfolded(!m_unfolded);
}

void BaseForm::init() {
    mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(m_titleBar);
    mainLayout->addWidget(m_widget);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    setLayout(mainLayout);
}
