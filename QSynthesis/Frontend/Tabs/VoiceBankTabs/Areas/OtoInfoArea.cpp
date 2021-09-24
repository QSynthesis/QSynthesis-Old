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
    lcName = new LineControl(Qt::Horizontal, tr("Name"), this);
    lcAuthor = new LineControl(Qt::Horizontal, tr("Author"), this);

    lbImage = new ImageLabel(this);
    lbImage->setFixedSize(100, 100);

    // Tabs
    infoTabs = new TabWidget(this);
    infoTabs->setProperty("type", "voice");

    readmeTab = new TextBoxTab(infoTabs);
    prefixTab = new PrefixMapTab(infoTabs);
    imageTab = new ImageTab(infoTabs);

    infoTabs->addTab(readmeTab, tr("Description"));
    infoTabs->addTab(prefixTab, tr("Pitch"));
    infoTabs->addTab(imageTab, tr("Foreground"));

    // Top Left Layout
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setVerticalSpacing(20);

    mainLayout->addWidget(lbImage, 0, 0, 2, 1);
    mainLayout->addWidget(lcName, 0, 1, 1, 1);
    mainLayout->addWidget(lcAuthor, 1, 1, 1, 1);
    mainLayout->addWidget(infoTabs, 2, 0, 1, 2);

    setLayout(mainLayout);

    connect(lbImage, &ImageLabel::reveal, this, &OtoInfoArea::handleRevealAvatar);
    connect(lbImage, &ImageLabel::replace, this, &OtoInfoArea::handleReplaceAvatar);
    connect(lbImage, &ImageLabel::remove, this, &OtoInfoArea::handleRemoveAvatar);

    connect(imageTab->content(), &ImageLabel::reveal, this, &OtoInfoArea::handleRevealSprite);
    connect(imageTab->content(), &ImageLabel::replace, this, &OtoInfoArea::handleReplaceSprite);
    connect(imageTab->content(), &ImageLabel::remove, this, &OtoInfoArea::handleRemoveSprite);

    connect(lcName->Text(), &FixedLineEdit::editingFinished2, this,
            &OtoInfoArea::handleNameChanged);
    connect(lcAuthor->Text(), &FixedLineEdit::editingFinished2, this,
            &OtoInfoArea::handleAuthorChanged);

    connect(prefixTab, &PrefixMapTab::prefixChanged, this, &OtoInfoArea::handlePrefixChanged);
    connect(prefixTab, &PrefixMapTab::suffixChanged, this, &OtoInfoArea::handleSuffixChanged);

    connect(readmeTab, &TextBoxTab::textChanged, this, &OtoInfoArea::handleTextChanged);

    resetAvatar();
    resetSprite();
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
    lcName->Text()->blockSignals(true);

    m_name = name;
    lcName->Text()->setText(name);

    lcName->Text()->blockSignals(false);
}

QString OtoInfoArea::author() const {
    return m_author;
}

void OtoInfoArea::setAuthor(const QString &author) {
    lcAuthor->Text()->blockSignals(true);

    m_author = author;
    lcAuthor->Text()->setText(author);

    lcAuthor->Text()->blockSignals(false);
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
