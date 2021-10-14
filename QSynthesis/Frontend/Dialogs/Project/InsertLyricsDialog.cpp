#include "InsertLyricsDialog.h"
#include "QUtauUtils.h"
#include "QUtils.h"
#include "application.h"

InsertLyricsDialog::InsertLyricsDialog(QStringList &lyrics, QWidget *parent)
    : BaseDialog(parent), orgLyrics(lyrics) {
    init();
}

InsertLyricsDialog::~InsertLyricsDialog() {
    qSetting->ignoreRestsWhenInsert = cbIgnore->isChecked();
    qSetting->replaceLyricsWhenInsert = cbReplace->isChecked();
    qSetting->separateCharWhenInsert = cbSplit->isChecked();
}

int InsertLyricsDialog::exec() {
    setResult(0);
    return BaseDialog::exec();
}

bool InsertLyricsDialog::ignoreRest() const {
    return cbIgnore->isChecked();
}

bool InsertLyricsDialog::replaceLyrics() const {
    return cbReplace->isChecked();
}

bool InsertLyricsDialog::separateIntoChar() const {
    return cbSplit->isChecked();
}

void InsertLyricsDialog::init() {
    setWindowTitle(tr("Insert Lyrics"));
    setFixedSize(450, 350);

    // 添加标签和按钮

    btnCancel = new QPushButton(tr("Cancel"), this);
    btnOK = new QPushButton(tr("OK"), this);
    btnReset = new QPushButton(tr("Reset"), this);

    tcLyrics = new TextControl(tr("Lyrics (Split by space)"), this);

    cbIgnore = new QCheckBox(tr("Ignore rests"), this);
    cbReplace = new QCheckBox(tr("Replace lyrics"), this);
    cbSplit = new QCheckBox(tr("Separate into characters"), this);

    cbIgnore->setChecked(qSetting->ignoreRestsWhenInsert);
    cbReplace->setChecked(qSetting->replaceLyricsWhenInsert);
    cbSplit->setChecked(qSetting->separateCharWhenInsert);

    btnCancel->setFixedSize(115, 35);
    btnOK->setFixedSize(115, 35);
    btnReset->setFixedSize(115, 35);

    btnOK->setShortcut(QKeySequence(Qt::Key_Return));
    btnCancel->setShortcut(QKeySequence(Qt::Key_Escape));

    connect(btnReset, &QPushButton::clicked, this, &InsertLyricsDialog::onResetClicked);
    connect(btnOK, &QPushButton::clicked, this, &InsertLyricsDialog::onOKClicked);
    connect(btnCancel, &QPushButton::clicked, this, &InsertLyricsDialog::onCancelClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(20);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(btnReset);
    buttonLayout->addWidget(btnOK);
    buttonLayout->addWidget(btnCancel);

    mainLayout->addWidget(tcLyrics);
    mainLayout->addWidget(cbIgnore);
    mainLayout->addWidget(cbReplace);
    mainLayout->addWidget(cbSplit);
    mainLayout->addLayout(buttonLayout);

    // Set first stage
    setDefaultLyrics();

    tcLyrics->Text()->setFocus();
    // tcLyrics->moveCursorToEnd();
    tcLyrics->Text()->selectAll();

    btnOK->setDefault(true);
}

void InsertLyricsDialog::setDefaultLyrics() {
    QStringList list;

    for (auto it = orgLyrics.begin(); it != orgLyrics.end(); ++it) {
        if (ignoreRest() && isRestNoteLyric(*it)) {
            continue;
        }
        if (!separateIntoChar()) {
            list.append(correctLyricBySpace(*it));
        } else {
            list.append(correctLyricByLength(*it));
        }
    }

    if (!separateIntoChar()) {
        tcLyrics->setValue(list.join(" "));
    } else {
        tcLyrics->setValue(list.join(""));
    }
}

void InsertLyricsDialog::onResetClicked() {
    setDefaultLyrics();
}

void InsertLyricsDialog::onOKClicked() {
    QString content = tcLyrics->getValue().trimmed();
    if (!separateIntoChar()) {
        orgLyrics = splitBySpace(content);
    } else {
        orgLyrics = splitByNone(content);
    }
    setResult(1);
    close();
}

void InsertLyricsDialog::onCancelClicked() {
    close();
}

int InsertLyricsDialog::findNextQuote(const QString &s, int n) {
    int q1 = s.indexOf('\'', n);
    int q2 = s.indexOf('\"', n);

    if (q1 < 0) {
        if (q2 >= 0) {
            q1 = q2;
        } else {
            q1 = s.size();
        }
    } else {
        if (q2 >= 0 && q2 < q1) {
            q1 = q2;
        }
    }

    return q1;
}

int InsertLyricsDialog::findNextSpace(const QString &s, int n) {
    int q1 = s.indexOf(' ', n);
    int q2 = s.indexOf('\n', n);

    if (q1 < 0) {
        if (q2 >= 0) {
            q1 = q2;
        } else {
            q1 = s.size();
        }
    } else {
        if (q2 >= 0 && q2 < q1) {
            q1 = q2;
        }
    }

    return q1;
}

QStringList InsertLyricsDialog::splitBySpace(const QString &content) {
    int i, q, s, j;
    bool isQuote = false;
    QString temp;

    QStringList list;

    i = 0;
    while (i < content.size()) {
        q = findNextQuote(content, i);
        s = findNextSpace(content, i);
        if (s < 0) {
            s = content.size();
        }

        if (isQuote) {
            j = q; // Find next quote
        } else {
            j = qMin(s, q); // Find next nearest space or quote
        }

        temp = content.mid(i, j - i);

        // is quote
        if (j < content.size() && (content[j] == '\'' || content[j] == '\"')) {
            isQuote = !isQuote;
        }

        if (!temp.isEmpty()) {
            list.append(temp);
        }
        i = j + 1;
    }

    return list;
}

QStringList InsertLyricsDialog::splitByNone(const QString &content) {
    QStringList list;
    QString temp;

    int i = 0, j;
    while (i < content.size()) {
        if (content[i] == '\'' || content[i] == '\"') {
            j = findNextQuote(content, i + 1);
            temp = content.mid(i + 1, j - i - 1);
        } else {
            j = i;
            temp = content[i];
        }
        list.push_back(temp);
        i = j + 1;
    }

    return list;
}

QString InsertLyricsDialog::correctLyricBySpace(const QString &lrc) {
    if (lrc.contains(' ')) {
        return '\"' + lrc + '\"';
    } else {
        return lrc;
    }
}

QString InsertLyricsDialog::correctLyricByLength(const QString &lrc) {
    if (lrc.size() > 1) {
        return '\"' + lrc + '\"';
    } else {
        return lrc;
    }
}
