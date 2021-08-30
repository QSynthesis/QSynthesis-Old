#include "TrackHead.h"
#include "../../Areas/Tracks/BlocksArea.h"
#include "../../Areas/Tracks/HeadsArea.h"
#include "Directory/VoiceInfo.h"

#include "../../TuningGroup.h"
#include "mainwindow.h"

TrackHead::TrackHead(HeadsArea *parent) : QWidget(parent), m_parent(parent) {
    init();
}

TrackHead::TrackHead(QString res, QString flags, QString name, QString voice, HeadsArea *parent)
    : QWidget(parent), m_parent(parent), m_resampler(res), m_flags(flags), m_name(name),
      m_voice(voice) {
    init();

    setResampler(res);
    setFlags(flags);
    setName(name);
    setVoiceDir(voice);
}

TrackHead::TrackHead(QString flags, QString name, QString voice, HeadsArea *parent)
    : QWidget(parent), m_parent(parent), m_flags(flags), m_name(name), m_voice(voice) {
    init();

    setFlags(flags);
    setName(name);
}

TrackHead::TrackHead(QString name, QString voice, HeadsArea *parent)
    : QWidget(parent), m_parent(parent), m_name(name), m_voice(voice) {
    init();

    setName(name);
}

void TrackHead::clear() {
    setResampler("");
    setFlags("");
    setName("");
    setVoiceDir("");
}

int TrackHead::mode() const {
    return m_mode;
}

void TrackHead::setMode(int mode) {
    m_mode = mode;
    updateStatus();
}

QString TrackHead::flags() const {
    return m_flags;
}

void TrackHead::setFlags(const QString &flags) {
    QString org = m_flags;
    m_flags = flags;
    emit flagsChanged(org, m_flags);
    if (m_mode == 2) {
        updateStatus();
    }
}

QString TrackHead::name() const {
    return m_name;
}

void TrackHead::setName(const QString &name) {
    QString org = m_name;
    m_name = name;
    emit nameChanged(org, m_name);

    if (m_mode == 1) {
        updateStatus();
    }
}

QString TrackHead::voiceDir() const {
    return m_voice;
}

void TrackHead::setVoiceDir(const QString &voice) {
    QString org = m_voice;
    m_voice = voice;
    emit voiceChanged(org, m_voice);

    loadVoiceInfo();
}

QString TrackHead::resampler() const {
    return m_resampler;
}

void TrackHead::setResampler(const QString &resampler) {
    QString org = m_resampler;
    m_resampler = resampler;
    emit resamplerChanged(org, m_resampler);

    if (m_mode == 2) {
        updateStatus();
    }
}

void TrackHead::updateStatus() {
    if (m_mode == 1) {
        lbNameFlags->setPlaceholderText(tr("Untitled Track"));
        lbNameFlags->setText(m_name);

        btnVoiceRes->setText(m_voice.isEmpty() ? tr("No Singer") : m_voiceTitle);
        btnVoiceRes->setToolTip(QDir::toNativeSeparators(m_voice));

        if (!m_voice.isEmpty() && !isDirExist(m_voice)) {
            btnVoiceRes->setProperty("invalid", "true");
            btnVoiceRes->setToolTip(tr("Invalid voice directory."));
        } else {
            btnVoiceRes->setProperty("invalid", "false");
        }
        style()->polish(btnVoiceRes);
    } else {
        lbNameFlags->setPlaceholderText("Flags");
        lbNameFlags->setText(m_flags);

        QString resStr = PathFindFileName(m_resampler);
        btnVoiceRes->setText(resStr.isEmpty() ? tr("No Resampler") : resStr);
        btnVoiceRes->setToolTip(QDir::toNativeSeparators(m_resampler));

        if (!m_resampler.isEmpty() && !isFileExist(m_resampler)) {
            btnVoiceRes->setProperty("invalid", "true");
            btnVoiceRes->setToolTip(tr("Invalid resampler path."));
        } else {
            btnVoiceRes->setProperty("invalid", "false");
        }
        style()->polish(btnVoiceRes);
    }
}

QColor TrackHead::iconColor() const {
    return m_iconColor;
}

void TrackHead::setIconColor(const QColor &iconColor) {
    m_iconColor = iconColor;
    reloadIcons();

    emit iconColorChanged();
}

void TrackHead::init() {
    m_resampler = "";
    m_flags = "";
    m_name = "";
    m_voice = "";

    setAttribute(Qt::WA_StyledBackground);
    setFocusPolicy(Qt::ClickFocus);

    m_iconColor = Qt::lightGray;

    trackLayout = new QHBoxLayout(this);

    labelLayout = new QVBoxLayout();
    dialLayout = new QGridLayout();
    buttonLayout = new QVBoxLayout();

    // labelLayout
    lbNameFlags = new FixedLineEdit(this);
    btnVoiceRes = new QPushButton(this);

    btnVoiceRes->setProperty("type", "label");
    btnVoiceRes->setProperty("invalid", "false");

    connect(lbNameFlags, &FixedLineEdit::editingFinished2, this, &TrackHead::onLineEditFinished);
    connect(btnVoiceRes, &QPushButton::clicked, this, &TrackHead::onLabelBtnClicked);

    setMode(1);

    labelLayout->addWidget(lbNameFlags);
    labelLayout->addWidget(btnVoiceRes);

    // dialLayout

    panDial = new QDial(this);
    volDial = new QDial(this);
    panDial->setFixedSize(30, 30);
    volDial->setFixedSize(30, 30);

    lbPanIcon = new QLabel(this);
    lbVolIcon = new QLabel(this);

    reloadIcons();

    dialLayout->addWidget(panDial, 0, 0, Qt::AlignCenter);
    dialLayout->addWidget(volDial, 0, 1, Qt::AlignCenter);
    dialLayout->addWidget(lbPanIcon, 1, 0, Qt::AlignCenter);
    dialLayout->addWidget(lbVolIcon, 1, 1, Qt::AlignCenter);

    // buttonLayout
    btnMute = new QPushButton("M", this);
    btnMute->setProperty("type", "letter");
    btnSolo = new QPushButton("S", this);
    btnSolo->setProperty("type", "letter");

    btnMute->setFixedSize(20, 20);
    btnSolo->setFixedSize(20, 20);

    btnMute->setCheckable(true);
    btnSolo->setCheckable(true);

    buttonLayout->addWidget(btnMute);
    buttonLayout->addWidget(btnSolo);

    trackLayout->addLayout(labelLayout);
    trackLayout->addLayout(dialLayout);
    trackLayout->addLayout(buttonLayout);

    setLayout(trackLayout);

    // Init menu
    m_menu = new QMenu(this);

    connect(&m_voiceInfo, &VoiceInfo::charTxtChanged, this, &TrackHead::handleVoiceInfoChanged);
}

void TrackHead::reloadIcons() {
    QPixmap bmpPanIcon =
        createBitmapFromSVG_W(":/images/TrackPanIcon.svg", QSize(18, 9), m_iconColor);
    QPixmap bmpVolIcon =
        createBitmapFromSVG_W(":/images/TrackVolIcon.svg", QSize(18, 9), m_iconColor);

    lbPanIcon->setPixmap(bmpPanIcon);
    lbVolIcon->setPixmap(bmpVolIcon);
}

void TrackHead::onLineEditFinished() {
    if (m_mode == 1) {
        setName(lbNameFlags->text());
    } else {
        setFlags(lbNameFlags->text());
    }
}

void TrackHead::onLabelBtnClicked() {
    if (m_mode == 1) {
        const QList<VoiceInfo *> dirs = voice->dirs();
        if (dirs.isEmpty()) {
            QAction *action = new QAction(tr("Null"), m_menu);
            m_menu->addAction(action);
        } else {
            for (int i = 0; i < dirs.size(); ++i) {
                VoiceInfo *voice = dirs.at(i);
                QAction *action = new QAction(voice->title(), m_menu);
                action->setData(voice->dirname());
                action->setCheckable(true);

                if (isSameFile(voice->dirname(), m_voice)) {
                    action->setChecked(true);
                }

                connect(action, &QAction::triggered, this, &TrackHead::onVoiceActionTriggered);
                m_menu->addAction(action);
            }
        }
        m_menu->addSeparator();

#if defined(_WIN32)
        QAction *openAction = new QAction(tr("Open in Explorer"), m_menu);
#elif defined(__APPLE__)
        QAction *openAction = new QAction(tr("Open in Finder"), m_menu);
#else
        QAction *openAction = new QAction(tr("Open in File manager"), m_menu);
#endif
        connect(openAction, &QAction::triggered, this, &TrackHead::onRevealActionTriggered);
        m_menu->addAction(openAction);

        QAction *action = new QAction(tr("Browse..."), m_menu);
        connect(action, &QAction::triggered, this, &TrackHead::onBrowseActionTriggered);
        m_menu->addAction(action);
    } else {
        m_menu->addSeparator();

#if defined(_WIN32)
        QAction *openAction = new QAction(tr("Show in Explorer"), m_menu);
#elif defined(__APPLE__)
        QAction *openAction = new QAction(tr("Show in Finder"), m_menu);
#else
        QAction *openAction = new QAction(tr("Show in File manager"), m_menu);
#endif
        connect(openAction, &QAction::triggered, this, &TrackHead::onRevealActionTriggered);
        m_menu->addAction(openAction);

        QAction *action = new QAction(tr("Browse..."), m_menu);
        connect(action, &QAction::triggered, this, &TrackHead::onBrowseActionTriggered);
        m_menu->addAction(action);
    }

    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void TrackHead::onVoiceActionTriggered() {
    QAction *action = qobject_cast<QAction *>(sender());
    QString path = action->data().toString();
    setVoiceDir(path);
}

void TrackHead::onBrowseActionTriggered() {
    if (m_mode == 1) {
        QString path = QFileDialog::getExistingDirectory(this, tr("Open Voice Bank"));
        if (!path.isEmpty()) {
            QString org = m_voice;
            m_parent->ptrs()->tab->switchToOtoReferenceMap(path);
            setVoiceDir(path);
        }
    } else {
        QString path =
            QFileDialog::getOpenFileName(this, tr("Set Resampler"), ".", toolsFilterString);
        if (!path.isEmpty()) {
            setResampler(path);
        }
    }
}

void TrackHead::onRevealActionTriggered() {
    if (m_mode == 1) {
        RevealFile(m_voice.isEmpty() ? voiceProfile() : m_voice);
    } else {
        RevealFile(m_resampler.isEmpty() ? AppPath : m_resampler);
    }
}

void TrackHead::loadVoiceInfo() {
    m_voiceTitle = PathFindFileName(m_voice);
    m_voiceInfo.setDirname(m_voice);
    if (m_voiceInfo.load()) {
        m_voiceTitle = m_voiceInfo.title();
    }

    if (m_mode == 1) {
        updateStatus();
    }
}

void TrackHead::handleVoiceInfoChanged() {
    loadVoiceInfo();
}
