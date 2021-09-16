#include "FormSplitter.h"

FormSplitter::FormSplitter(QWidget *parent) : QSplitter(Qt::Vertical, parent) {
    forms.clear();
    topWidget = nullptr;
    mainIndex = 0;

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

    disconnect(form, &BaseForm::visibilityChanged, this,
               &FormSplitter::onFormVisibilityChanged);
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
        mainIndex = index;
    }
}

void FormSplitter::setMainForm(BaseForm *form) {
    int index = forms.indexOf(form);
    if (index >= 0) {
        mainIndex = index;
    }
}

int FormSplitter::MainIndex() {
    return mainIndex;
}

void FormSplitter::onFormVisibilityChanged(bool b) {
    BaseForm *form = qobject_cast<BaseForm *>(sender());

    int i;
    bool flag = false;
    int index = forms.indexOf(form);

    if (index < 0 || topWidget) {
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
        if (index == mainIndex) {
            int i = (mainIndex == forms.size() - 1) ? (mainIndex - 1) : (mainIndex + 1);
            forms[i]->reverseFold();
        } else {
            forms[mainIndex]->reverseFold();
        }
    }
    modifyFeatures();

    emit statusChanged();
}

void FormSplitter::modifyFeatures() {
    int i;

    for (i = 0; i < forms.size(); ++i) {
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
    int i;

    for (i = 0; i < forms.size(); ++i) {
        if (!forms[i]->unfolded()) {
            setStretchFactor(i, 1);
        }
    }
}
