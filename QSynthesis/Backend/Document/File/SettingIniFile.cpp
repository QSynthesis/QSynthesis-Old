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
        QString *ignoreRestString = tempSection->valueOf(KEY_NAME_INSERT_IGNORE_RESTS);
        if (ignoreRestString) {
            m_data.ignoreRestsWhenInsert = *ignoreRestString == "True";
        }
        QString *replaceLyricsString = tempSection->valueOf(KEY_NAME_INSERT_REPLACE_LYRICS);
        if (replaceLyricsString) {
            m_data.replaceLyricsWhenInsert = *replaceLyricsString == "True";
        }
        QString *splitCharString = tempSection->valueOf(KEY_NAME_INSERT_SEPARATE_CHAR);
        if (ignoreRestString) {
            m_data.separateCharWhenInsert = *splitCharString == "True";
        }
        QString *lastQuantizeString = tempSection->valueOf(KEY_NAME_LAST_QUANTIZE);
        if (lastQuantizeString) {
            QSet<int> values{0, 1, 2, 4, 6, 8, 16, 24, 32};
            int num = lastQuantizeString->toInt();
            if (values.contains(num)) {
                m_data.lastQuantize = num;
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
        QString *tracksFromV = guiSection->valueOf(KEY_NAME_TRACKS_FORM_VISIBILITY);
        if (tracksFromV) {
            m_data.tracksFormVisibility = *tracksFromV == "True";
        }
        QString *editorFormV = guiSection->valueOf(KEY_NAME_EDITOR_FORM_VISIBILITY);
        if (editorFormV) {
            m_data.editorFormVisibility = *editorFormV == "True";
        }
        QString *paramsForm = guiSection->valueOf(KEY_NAME_PARAMS_FORM_VISIBILITY);
        if (paramsForm) {
            m_data.paramsFormVisibility = *paramsForm == "True";
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
    tempSection.addPair(KEY_NAME_INSERT_IGNORE_RESTS,
                        m_data.ignoreRestsWhenInsert ? "True" : "False");
    tempSection.addPair(KEY_NAME_INSERT_REPLACE_LYRICS,
                        m_data.replaceLyricsWhenInsert ? "True" : "False");
    tempSection.addPair(KEY_NAME_INSERT_SEPARATE_CHAR,
                        m_data.separateCharWhenInsert ? "True" : "False");
    tempSection.addPair(KEY_NAME_LAST_QUANTIZE, QString::number(m_data.lastQuantize));
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
    guiSection.addPair(KEY_NAME_TRACKS_FORM_VISIBILITY,
                       m_data.tracksFormVisibility ? "True" : "False");
    guiSection.addPair(KEY_NAME_EDITOR_FORM_VISIBILITY,
                       m_data.editorFormVisibility ? "True" : "False");
    guiSection.addPair(KEY_NAME_PARAMS_FORM_VISIBILITY,
                       m_data.paramsFormVisibility ? "True" : "False");
    guiSection.addPair(KEY_NAME_THEME_INDEX, QString::number(m_data.themeIndex));

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
