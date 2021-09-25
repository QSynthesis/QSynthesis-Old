#include "SettingIniFile.h"
#include "Import/QSettingFile.h"
#include "UTAU/Strings/UtaSettingText.h"
#include "Utils/Templates.h"

using namespace UtaSettingText;

QTextCodec *SettingIniFile::defaultCodec = nullptr;

SettingIniFile::SettingIniFile(QObject *parent) : FileManager(parent) {
    m_codec = defaultCodec;
    reset();
}

SettingIniFile::SettingIniFile(const QString &filename, QObject *parent) : FileManager(parent) {
    m_codec = defaultCodec;
    setFilename(filename);
}

SettingIniFile::~SettingIniFile() {
}

bool SettingIniFile::loadCore(bool *valid) {
    QSettingFile setting;
    setting.setCodec(m_codec);

    if (!setting.load(m_filename)) {
        return false;
    }

    // Temporary
    QSettingSection *tempSection = setting.sectionOf(SECTION_NAME_TEMP);
    if (tempSection) {
        QString *tool1 = tempSection->valueOf(KEY_NAME_TOOL1_PATH);
        if (tool1) {
            m_data.tool1Path = QDir::fromNativeSeparators(*tool1);
        }
        QString *tool2 = tempSection->valueOf(KEY_NAME_TOOL2_PATH);
        if (tool2) {
            m_data.tool2Path = QDir::fromNativeSeparators(*tool2);
        }
        QString *insertLyric = tempSection->valueOf(KEY_NAME_INSERT_LYRICS_STATE);
        if (insertLyric) {
            bool isNum;
            int code = insertLyric->toInt(&isNum);
            if (isNum) {
                m_data.ignoreRestsWhenInsert = code & 0x1;
                m_data.replaceLyricsWhenInsert = code & 0x2;
                m_data.separateCharWhenInsert = code & 0x4;
            }
        }
    }

    // Projects
    QSettingSection *projectsSection = setting.sectionOf(SECTION_NAME_PROJECT);
    if (projectsSection && projectsSection->isArray()) {
        QList<QString> list = projectsSection->toArray();
        for (int i = 0; i < list.size(); ++i) {
            m_data.projects.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Voice Banks
    QSettingSection *foldersSection = setting.sectionOf(SECTION_NAME_VOICE);
    if (foldersSection && foldersSection->isArray()) {
        QStringList list = foldersSection->toArray();
        for (int i = 0; i < list.size(); ++i) {
            m_data.folders.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Wavtools
    QSettingSection *wavtoolsSection = setting.sectionOf(SECTION_NAME_WAVTOOL);
    if (wavtoolsSection && wavtoolsSection->isArray()) {
        QStringList list = wavtoolsSection->toArray();
        for (int i = 0; i < list.size(); ++i) {
            m_data.wavtools.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Resamplers
    QSettingSection *resamplersSection = setting.sectionOf(SECTION_NAME_RESAMPLER);
    if (resamplersSection && resamplersSection->isArray()) {
        QStringList list = resamplersSection->toArray();
        for (int i = 0; i < list.size(); ++i) {
            m_data.resamplers.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // GUI
    QSettingSection *guiSection = setting.sectionOf(SECTION_NAME_GUI);
    if (guiSection) {
        QString *windowString = guiSection->valueOf(KEY_NAME_MAINWINDOW);
        if (windowString) {
            QStringList list = windowString->split(",");
            if (list.size() > 4) {
                m_data.windowRect.setX(list[0].toInt());
                m_data.windowRect.setY(list[1].toInt());
                m_data.windowRect.setWidth(list[2].toInt());
                m_data.windowRect.setHeight(list[3].toInt());
                m_data.windowMaximized = list[4].toInt();
            }
        }
        QString *lastQuantizeString = tempSection->valueOf(KEY_NAME_LAST_QUANTIZE);
        if (lastQuantizeString) {
            QSet<int> values{0, 1, 2, 4, 6, 8, 16, 24, 32};
            int num = lastQuantizeString->toInt();
            if (values.contains(num)) {
                m_data.lastQuantize = num;
            }
        }
        QString *formsVisible = guiSection->valueOf(KEY_NAME_FORMS_VISIBILITY);
        if (formsVisible) {
            bool isNum;
            int code = formsVisible->toInt(&isNum);
            if (isNum) {
                m_data.tracksFormVisibility = code & 0x1;
                m_data.editorFormVisibility = code & 0x2;
                m_data.paramsFormVisibility = code & 0x4;
            }
        }
        QString *elementsState = guiSection->valueOf(KEY_NAME_ELEMENTS_STATE);
        if (elementsState) {
            bool isNum;
            int code = elementsState->toInt(&isNum);
            if (isNum) {
                m_data.noteVisibility = code & 0x1;
                m_data.pitchVisibility = code & 0x2;
                m_data.envelopeVisibility = code & 0x4;
                m_data.paramsVisibility = code & 0x8;
            }
        }
        QString *playHeadState = guiSection->valueOf(KEY_NAME_PLAYHEAD_STATE);
        if (playHeadState) {
            bool isNum;
            int code = playHeadState->toInt(&isNum);
            if (isNum) {
                m_data.playHeadCenter = code == 1;
            }
        }
        QString *foregroundState = guiSection->valueOf(KEY_NAME_FOREGROUND_STATE);
        if (foregroundState) {
            bool isNum;
            int code = foregroundState->toInt(&isNum);
            if (isNum) {
                m_data.spriteOpacity = double(code & 0x7F) / 100;
                m_data.spriteVisibility = (code >> 7) & 0x1;
                m_data.spritePosition = static_cast<Qt::Corner>(code >> 8);
            }
        }
        QString *themeIndex = guiSection->valueOf(KEY_NAME_THEME_INDEX);
        if (themeIndex) {
            m_data.themeIndex = themeIndex->toInt();
        }
    }
    return true;
}

bool SettingIniFile::saveCore() {
    QSettingFile setting;
    setting.setCodec(m_codec);

    // Temporary
    QSettingSection tempSection(SECTION_NAME_TEMP);
    QFileInfo tool1File(m_data.tool1Path), tool2File(m_data.tool2Path);
    if (tool1File.isFile()) {
        tempSection.addPair(KEY_NAME_TOOL1_PATH,
                            QDir::toNativeSeparators(tool1File.absoluteFilePath()));
    }
    if (tool2File.isFile()) {
        tempSection.addPair(KEY_NAME_TOOL2_PATH,
                            QDir::toNativeSeparators(tool2File.absoluteFilePath()));
    }
    tempSection.addPair(KEY_NAME_INSERT_LYRICS_STATE, m_data.ignoreRestsWhenInsert +
                                                          (m_data.replaceLyricsWhenInsert << 1) +
                                                          (m_data.separateCharWhenInsert << 2));
    setting.addSection(tempSection);

    // Projects
    QStringList fileList = m_data.projects.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_PROJECT, KEY_PREFIX_PROJECT,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Voice Banks
    fileList = m_data.folders.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_VOICE, KEY_PREFIX_VOICE,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Wavtools
    fileList = m_data.wavtools.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_WAVTOOL, KEY_PREFIX_WAVTOOL,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Resamplers
    fileList = m_data.resamplers.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_RESAMPLER, KEY_PREFIX_RESAMPLER,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Main Window Coordinates
    QSettingSection guiSection(SECTION_NAME_GUI);

    QString windowString;
    QTextStream stream(&windowString);
    stream << m_data.windowRect.x() << "," << m_data.windowRect.y() << ","
           << m_data.windowRect.width() << "," << m_data.windowRect.height() << ","
           << m_data.windowMaximized;

    guiSection.addPair(KEY_NAME_MAINWINDOW, windowString);
    tempSection.addPair(KEY_NAME_LAST_QUANTIZE, m_data.lastQuantize);
    guiSection.addPair(KEY_NAME_FORMS_VISIBILITY, m_data.tracksFormVisibility +
                                                      (m_data.editorFormVisibility << 1) +
                                                      (m_data.paramsFormVisibility << 2));
    guiSection.addPair(KEY_NAME_ELEMENTS_STATE,
                       m_data.noteVisibility + (m_data.pitchVisibility << 1) +
                           (m_data.envelopeVisibility << 2) + (m_data.paramsFormVisibility << 3));
    guiSection.addPair(KEY_NAME_PLAYHEAD_STATE, m_data.playHeadCenter ? 1 : 0);
    guiSection.addPair(KEY_NAME_FOREGROUND_STATE, int(m_data.spriteOpacity * 100) +
                                                      (m_data.spriteVisibility << 7) +
                                                      (m_data.spritePosition << 8));
    guiSection.addPair(KEY_NAME_THEME_INDEX, m_data.themeIndex);

    setting.addSection(guiSection);

    return setting.save(m_filename);
}

void SettingIniFile::resetCore() {
    m_data.clear();
}

SettingIniData SettingIniFile::data() const {
    return m_data;
}

void SettingIniFile::setData(const SettingIniData &data) {
    m_data = data;
}

QTextCodec *SettingIniFile::codec() const {
    return m_codec;
}

void SettingIniFile::setCodec(QTextCodec *codec) {
    m_codec = codec;
}

QTextCodec *SettingIniFile::codeForDefault() {
    return defaultCodec;
}

void SettingIniFile::setCodeForDefault(QTextCodec *codec) {
    defaultCodec = codec;
}
