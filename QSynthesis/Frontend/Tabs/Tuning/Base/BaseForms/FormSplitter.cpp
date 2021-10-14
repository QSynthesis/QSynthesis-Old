#include "FormSplitter.h"
#include "../BaseForm.h"

FormSplitter::FormSplitter(QWidget *parent) : QSplitter(Qt::Vertical, parent) {
    forms.clear();
    topWidget = nullptr;
    m_mainIndex = 0;
    m_autoUnfold = false;

    setHandleWidth(3);
    setFrameStyle(QFrame::NoFrame);

    setChildrenCollapsible(false);
}

void FormSplitter::addForm(BaseForm *form, int stretch) {
    forms.append(form);
    QSplitter::addWidget(form);

    connect(form, &BaseForm::visibilityChanged, this, &FormSplitter::onFormVisibilityChanged);
    modifyFeatures();
}

void FormSplitter::insertForm(int index, BaseForm *form, int stretch) {
    forms.insert(index, form);
    QSplitter::insertWidget(index, form);

    connect(form, &BaseForm::visibilityChanged, this, &FormSplitter::onFormVisibilityChanged);

    modifyFeatures();
}

void FormSplitter::removeForm(BaseForm *form) {
    forms.removeOne(form);

    disconnect(form, &BaseForm::visibilityChanged, this, &FormSplitter::onFormVisibilityChanged);
    modifyFeatures();
}

void FormSplitter::setTopWidget(QWidget *w, int stretch) {
    if (!topWidget) {
        insertWidget(0, w);
        topWidget = w;
        modifyFeatures();
    }
}

void FormSplitter::removeTopWidget() {
    if (topWidget) {
        delete topWidget;
        topWidget = nullptr;
        modifyFeatures();
    }
}

void FormSplitter::setStretchFactor(QWidget *w, int stretch) {
    int index = indexOf(w);
    if (index < 0) {
        return;
    }
    setStretchFactor(index, stretch);
}

void FormSplitter::setStretchFactor(int index, int stretch) {
    QSplitter::setStretchFactor(index, stretch);
}

void FormSplitter::setMainIndex(int index) {
    if (index < forms.size()) {
        m_mainIndex = index;
    }
}

void FormSplitter::setMainForm(BaseForm *form) {
    int index = forms.indexOf(form);
    if (index >= 0) {
        m_mainIndex = index;
    }
}

int FormSplitter::mainIndex() const {
    return m_mainIndex;
}

bool FormSplitter::autoUnfold() const {
    return m_autoUnfold;
}

void FormSplitter::setAutoUnfold(bool autoUnfold) {
    m_autoUnfold = autoUnfold;
}

void FormSplitter::onFormVisibilityChanged(bool b) {
    BaseForm *form = qobject_cast<BaseForm *>(sender());

    int i;
    bool flag = false;
    int index = forms.indexOf(form);

    if (index < 0 || (topWidget && !m_autoUnfold)) {
        modifyFeatures();
        return;
    }

    for (i = 0; i < forms.size(); ++i) {
        if (forms[i]->unfolded()) {
            flag = true;
            break;
        }
    }

    // All forms have been folded
    if (!flag) {
        if (index == m_mainIndex) {
            int i = (m_mainIndex == forms.size() - 1) ? (m_mainIndex - 1) : (m_mainIndex + 1);
            forms[i]->reverseFold();
        } else {
            forms[m_mainIndex]->reverseFold();
        }
    }
    modifyFeatures();

    emit statusChanged();
}

void FormSplitter::modifyFeatures() {
    for (int i = 0; i < forms.size(); ++i) {
        if ((i == 0 && !topWidget) || (i > 0 && !forms[i - 1]->unfolded())) {
            forms[i]->titleBar()->setTopVisible(false);
            handle(indexOf(forms[i]))->setEnabled(false);
        } else {
            forms[i]->titleBar()->setTopVisible(true);
            handle(indexOf(forms[i]))->setEnabled(true);
        }

        if (i == forms.size() - 1 && !forms[i]->unfolded()) {
            handle(indexOf(forms[i]))->setEnabled(false);
        }
    }

    modifyStretches();
}

void FormSplitter::modifyStretches() {
    for (int i = 0; i < forms.size(); ++i) {
        if (!forms[i]->unfolded()) {
            setStretchFactor(i, 1);
        }
    }
}
