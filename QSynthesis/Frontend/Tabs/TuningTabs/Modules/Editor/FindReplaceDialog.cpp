#include "FindReplaceDialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) : TransparentContainer(parent) {
    m_current = 0;
    m_total = 0;

    mainLayout = new QGridLayout(this);
    mainLayout->setVerticalSpacing(10);

    findEdit = new FixedLineEdit();
    replaceEdit = new FixedLineEdit();

    findEdit->setPlaceholderText(tr("Find"));
    replaceEdit->setPlaceholderText(tr("Replace"));

    findEdit->setClearButtonEnabled(true);
    replaceEdit->setClearButtonEnabled(true);

    btnCase = new TextButton("Aa");
    btnWord = new TextButton("W");
    btnReserve = new TextButton("AB");

    btnCase->setToolTip(tr("Case sensitive"));
    btnWord->setToolTip(tr("Whole words only"));
    btnReserve->setToolTip(tr("Preserve case"));

    btnCase->setCheckable(true);
    btnWord->setCheckable(true);
    btnReserve->setCheckable(true);

    QSize btnSize1(30, 30);
    btnCase->setFixedSize(btnSize1);
    btnWord->setFixedSize(btnSize1);
    btnReserve->setFixedSize(btnSize1);

    QFrame *separator = new QFrame();
    separator->setProperty("type", "finder-separator");
    separator->setFrameStyle(QFrame::VLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setFixedWidth(1);

    lbResult = new QLabel();
    lbResult->setMinimumWidth(100);
    lbResult->setProperty("type", "finder-result");
    lbResult->setAlignment(Qt::AlignCenter);

    QSizeF padding(5, 5);
    QSizeF padding2(8, 8);
    QSize btnSize2(30, 30);

    btnPrev = new IconButton(padding);
    btnNext = new IconButton(padding);
    btnReplace = new IconButton(padding);
    btnReplaceAll = new IconButton(padding);
    btnClose = new IconButton(padding2);

    btnPrev->setIcon(":/images/arrow-left-line.svg");
    btnNext->setIcon(":/images/arrow-right-line.svg");
    btnReplace->setIcon(":/images/find-replace-line.svg");
    btnReplaceAll->setIcon(":/images/file-search-line.svg");
    btnClose->setIcon(":/images/close-line.svg");

    btnPrev->setToolTip(tr("Previous occurrence"));
    btnNext->setToolTip(tr("Next occurrence"));
    btnReplace->setToolTip(tr("Replace"));
    btnReplaceAll->setToolTip(tr("Replace all"));

    btnNext->setFixedSize(btnSize2);
    btnPrev->setFixedSize(btnSize2);
    btnReplace->setFixedSize(btnSize2);
    btnReplaceAll->setFixedSize(btnSize2);
    btnClose->setFixedSize(btnSize2);

    setFocusPolicy(Qt::ClickFocus);
    findEdit->setFocusPolicy(Qt::ClickFocus);
    replaceEdit->setFocusPolicy(Qt::ClickFocus);

    installEventFilter(this);
    findEdit->installEventFilter(this);
    replaceEdit->installEventFilter(this);

    connect(btnCase, &TextButton::toggled, this, &FindReplaceDialog::handleCaseBtnToggled);
    connect(btnWord, &TextButton::toggled, this, &FindReplaceDialog::handleWordBtnToggled);

    connect(btnPrev, &IconButton::clicked, this, &FindReplaceDialog::handlePrevBtnClicked);
    connect(btnNext, &IconButton::clicked, this, &FindReplaceDialog::handleNextBtnClicked);
    connect(btnReplace, &IconButton::clicked, this, &FindReplaceDialog::handleReplaceBtnClicked);
    connect(btnReplaceAll, &IconButton::clicked, this,
            &FindReplaceDialog::handleReplaceAllBtnClicked);

    connect(findEdit, &FixedLineEdit::textChanged, this, &FindReplaceDialog::handleFindTextChanged);

    connect(btnClose, &IconButton::clicked, this, &FindReplaceDialog::handleCloseBtnClicked);

    mainLayout->addWidget(findEdit, 0, 0);
    mainLayout->addWidget(replaceEdit, 1, 0, 1, 2);
    mainLayout->addWidget(btnCase, 0, 1);
    mainLayout->addWidget(btnWord, 0, 2);
    mainLayout->addWidget(btnReserve, 1, 2);
    mainLayout->addWidget(separator, 0, 3, 2, 1);
    mainLayout->addWidget(lbResult, 0, 4);

    mainLayout->addWidget(btnPrev, 0, 5);
    mainLayout->addWidget(btnNext, 0, 6);
    mainLayout->addWidget(btnClose, 0, 7);

    mainLayout->addWidget(btnReplace, 1, 5);
    mainLayout->addWidget(btnReplaceAll, 1, 6);

    setLayout(mainLayout);

    updateCaption();
    setMinimumWidth(500);
}

FindReplaceDialog::~FindReplaceDialog() {
}

bool FindReplaceDialog::matchCase() const {
    return btnCase->isChecked();
}

bool FindReplaceDialog::matchWord() const {
    return btnWord->isChecked();
}

bool FindReplaceDialog::preserveCase() const {
    return btnReserve->isChecked();
}

QString FindReplaceDialog::findText() const {
    return findEdit->text();
}

QString FindReplaceDialog::replaceText() const {
    return replaceEdit->text();
}

int FindReplaceDialog::current() const {
    return m_current;
}

void FindReplaceDialog::setCurrent(int current) {
    m_current = current;
    updateCaption();
}

int FindReplaceDialog::total() const {
    return m_total;
}

void FindReplaceDialog::setTotal(int total) {
    m_total = total;
    updateCaption();
}

void FindReplaceDialog::updateCaption() {
    lbResult->setText(QString::number(m_current) + "/" + QString::number(m_total));
}

void FindReplaceDialog::handleCaseBtnToggled(bool checked) {
    emit findStateChanged();
}

void FindReplaceDialog::handleWordBtnToggled(bool checked) {
    emit findStateChanged();
}

void FindReplaceDialog::handleReserveBtnToggled(bool checked) {
}

void FindReplaceDialog::handlePrevBtnClicked() {
    emit prevRequested();
}

void FindReplaceDialog::handleNextBtnClicked() {
    emit nextRequested();
}

void FindReplaceDialog::handleReplaceBtnClicked() {
    emit replaceRequested();
}

void FindReplaceDialog::handleReplaceAllBtnClicked() {
    emit replaceAllRequested();
}

void FindReplaceDialog::handleFindTextChanged(const QString &text) {
    emit findStateChanged();
}

void FindReplaceDialog::handleCloseBtnClicked() {
    emit closeRequested();
}

void FindReplaceDialog::focusInEvent(QFocusEvent *event) {
    findEdit->setFocus();
    findEdit->selectAll();
}

bool FindReplaceDialog::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            emit nextRequested();
            return true;
        }
    }
    return TransparentContainer::eventFilter(obj, event);
}
