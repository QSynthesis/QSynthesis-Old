#include "OtoInfoArea.h"

OtoInfoArea::OtoInfoArea(VoiceBankTab *tab, QWidget *parent) : VoiceBankArea(tab, parent) {
    init();
}

OtoInfoArea::~OtoInfoArea() {
}

void OtoInfoArea::initExtern() {
}

void OtoInfoArea::init() {
    // Labels
    lbName = new QLabel(tr("Name"), this);
    lbAuthor = new QLabel(tr("Author"), this);
    lbImage = new ImageLabel(this);
    lbImage->setFixedSize(100, 100);

    // Texts
    txtName = new FixedLineEdit(this);
    txtAuthor = new FixedLineEdit(this);

    // Tabs
    infoTabs = new TabWidget(this);
    infoTabs->setProperty("type", "voice");
    readmeTab = new TextBoxTab(infoTabs);
    prefixTab = new PrefixMapTab(infoTabs);

    infoTabs->addTab(readmeTab, tr("Description"));
    infoTabs->addTab(prefixTab, tr("Pitch"));

    // Top Left Layout
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(10);

    mainLayout->addWidget(lbImage, 0, 0, 2, 1);
    mainLayout->addWidget(lbName, 0, 1, 1, 1);
    mainLayout->addWidget(txtName, 0, 2, 1, 1);
    mainLayout->addWidget(lbAuthor, 1, 1, 1, 1);
    mainLayout->addWidget(txtAuthor, 1, 2, 1, 1);
    mainLayout->addWidget(infoTabs, 2, 0, 4, 3);

    mainLayout->setColumnStretch(0, 0);
    mainLayout->setColumnStretch(1, 0);
    mainLayout->setColumnStretch(2, 2);

    setLayout(mainLayout);

    connect(lbImage, &ImageLabel::reveal, this, &OtoInfoArea::handleRevealAvatar);
    connect(lbImage, &ImageLabel::replace, this, &OtoInfoArea::handleReplaceAvatar);
    connect(lbImage, &ImageLabel::remove, this, &OtoInfoArea::handleRemoveAvatar);

    connect(txtName, &FixedLineEdit::editingFinished2, this, &OtoInfoArea::handleNameChanged);
    connect(txtAuthor, &FixedLineEdit::editingFinished2, this, &OtoInfoArea::handleAuthorChanged);

    connect(prefixTab, &PrefixMapTab::prefixChanged, this, &OtoInfoArea::handlePrefixChanged);
    connect(prefixTab, &PrefixMapTab::suffixChanged, this, &OtoInfoArea::handleSuffixChanged);

    connect(readmeTab, &TextBoxTab::textChanged, this, &OtoInfoArea::handleTextChanged);

    resetAvatar();
}

QMap<int, QString> OtoInfoArea::prefixMap() const {
    return m_prefixMap;
}

void OtoInfoArea::setPrefixMap(const QMap<int, QString> &prefixMap) {
    m_prefixMap = prefixMap;

    for (auto it = prefixMap.begin(); it != prefixMap.end(); ++it) {
        prefixTab->setPrefix(it.key(), it.value());
    }
}

QMap<int, QString> OtoInfoArea::suffixMap() const {
    return m_suffixMap;
}

void OtoInfoArea::setSuffixMap(const QMap<int, QString> &suffixMap) {
    m_suffixMap = suffixMap;

    for (auto it = suffixMap.begin(); it != suffixMap.end(); ++it) {
        prefixTab->setSuffix(it.key(), it.value());
    }
}

QString OtoInfoArea::name() const {
    return m_name;
}

void OtoInfoArea::setName(const QString &name) {
    txtName->blockSignals(true);

    m_name = name;
    txtName->setText(name);

    txtName->blockSignals(false);
}

QString OtoInfoArea::author() const {
    return m_author;
}

void OtoInfoArea::setAuthor(const QString &author) {
    txtAuthor->blockSignals(true);

    m_author = author;
    txtAuthor->setText(author);

    txtAuthor->blockSignals(false);
}

QString OtoInfoArea::text() const {
    return m_text;
}

void OtoInfoArea::setText(const QString &text) {
    m_text = text;
    readmeTab->setText(text);
}

void OtoInfoArea::locatePrefix(int noteNum) {
    infoTabs->setCurrentWidget(prefixTab);
    prefixTab->selectTone(noteNum);
}
