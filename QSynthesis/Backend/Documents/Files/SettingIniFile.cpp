#include "SettingIniFile.h"
#include "Constants.h"
#include "Primary.h"
#include "QSettingFile.h"
#include "QUtauStrCore.h"

using namespace Utau;

Q_CHARSET_DECLARE(SettingIniFile)

SettingIniFile::SettingIniFile() : BaseFile(Qs::Default) {
    init();
    reset();
}

SettingIniFile::SettingIniFile(const QString &filename) : BaseFile(Qs::Default) {
    init();
    setFilename(filename);
}

SettingIniFile::~SettingIniFile() {
}

void SettingIniFile::init() {
    m_codec = defaultCodec;
    projects.setType(QFileSet::File);
    folders.setType(QFileSet::Directory);
    wavtools.setType(QFileSet::File);
    resamplers.setType(QFileSet::File);
}

bool SettingIniFile::loadCore(bool *valid) {
    QSettingFile setting;
    setting.setCodec(m_codec);

    if (!setting.load(m_filename)) {
        return false;
    }

    // Temporary
    QSettingSection *secTemp = setting.sectionOf(SECTION_NAME_TEMP);
    if (secTemp) {
        QString *sTool1 = secTemp->valueOf(KEY_NAME_TOOL1_PATH);
        if (sTool1) {
            tool1Path = QDir::fromNativeSeparators(*sTool1);
        }
        QString *sTool2 = secTemp->valueOf(KEY_NAME_TOOL2_PATH);
        if (sTool2) {
            tool2Path = QDir::fromNativeSeparators(*sTool2);
        }
        QString *sInsertLyric = secTemp->valueOf(KEY_NAME_INSERT_LYRICS_STATE);
        if (sInsertLyric) {
            QList<int> list = toIntList(sInsertLyric->split(","));
            if (list.size() == 3) {
                ignoreRestsWhenInsert = list.at(0);
                replaceLyricsWhenInsert = list.at(1);
                separateCharWhenInsert = list.at(2);
            }
        }
    }

    // Projects
    QSettingSection *secProjs = setting.sectionOf(SECTION_NAME_PROJECT);
    if (secProjs && secProjs->isArray()) {
        QList<QString> list = secProjs->toArray();
        for (int i = 0; i < list.size(); ++i) {
            projects.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Voice Banks
    QSettingSection *secVoices = setting.sectionOf(SECTION_NAME_VOICE);
    if (secVoices && secVoices->isArray()) {
        QStringList list = secVoices->toArray();
        for (int i = 0; i < list.size(); ++i) {
            folders.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Wavtools
    QSettingSection *secWavtools = setting.sectionOf(SECTION_NAME_WAVTOOL);
    if (secWavtools && secWavtools->isArray()) {
        QStringList list = secWavtools->toArray();
        for (int i = 0; i < list.size(); ++i) {
            wavtools.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // Resamplers
    QSettingSection *secResamps = setting.sectionOf(SECTION_NAME_RESAMPLER);
    if (secResamps && secResamps->isArray()) {
        QStringList list = secResamps->toArray();
        for (int i = 0; i < list.size(); ++i) {
            resamplers.push(QDir::fromNativeSeparators(list.at(i)));
        }
    }

    // GUI
    QSettingSection *secGUI = setting.sectionOf(SECTION_NAME_GUI);
    if (secGUI) {
        // Main Window
        QString *sWindow = secGUI->valueOf(KEY_NAME_MAINWINDOW);
        if (sWindow) {
            QList<int> list = toIntList(sWindow->split(","));
            if (list.size() > 4) {
                windowRect.setX(list.at(0));
                windowRect.setY(list.at(1));
                windowRect.setWidth(list.at(2));
                windowRect.setHeight(list.at(3));
                windowMaximized = list.at(4);
            }
        }
        // Quantization
        QString *sLastQuantize = secGUI->valueOf(KEY_NAME_LAST_QUANTIZE);
        if (sLastQuantize) {
            QSet<int> values{0, 1, 2, 4, 6, 8, 16, 24, 32};
            QList<int> list = toIntList({*sLastQuantize});
            if (list.size() == 1) {
                int num = list.front();
                if (values.contains(num)) {
                    lastQuantize = num;
                }
            }
        }
        // Forms
        QString *sFormVisible = secGUI->valueOf(KEY_NAME_FORMS_VISIBILITY);
        if (sFormVisible) {
            QList<int> list = toIntList(sFormVisible->split(","));
            if (list.size() == 3) {
                tracksFormVisibility = list.at(0);
                editorFormVisibility = list.at(1);
                paramsFormVisibility = list.at(2);
            }
        }
        // Note, Pitch, Envelope, Params
        QString *sElements = secGUI->valueOf(KEY_NAME_ELEMENTS_STATE);
        if (sElements) {
            QList<int> list = toIntList(sElements->split(","));
            if (list.size() == 4) {
                noteVisibility = list.at(0);
                pitchVisibility = list.at(1);
                envelopeVisibility = list.at(2);
                paramsVisibility = list.at(3);
            }
        }
        // Playhead
        QString *sPlayHead = secGUI->valueOf(KEY_NAME_PLAYHEAD_STATE);
        if (sPlayHead) {
            QList<int> list = toIntList({*sPlayHead});
            if (list.size() == 1) {
                playHeadCenter = list.front();
            }
        }
        // Foreground
        QString *sForeground = secGUI->valueOf(KEY_NAME_FOREGROUND_STATE);
        if (sForeground) {
            QList<int> list = toIntList(sForeground->split(","));
            if (list.size() == 3) {
                spriteOpacity = double(list.at(0)) / 100;
                spriteVisibility = list.at(1);
                int code = list.at(2);
                if (code >= 0 && code <= 3) {
                    envelopeVisibility = static_cast<Qt::Corner>(code);
                }
            }
        }
        // Theme
        QString *sTheme = secGUI->valueOf(KEY_NAME_THEME_INDEX);
        if (sTheme) {
            themeIndex = sTheme->toInt();
        }
    }
    return true;
}

bool SettingIniFile::saveCore() {
    QSettingFile setting;
    setting.setCodec(m_codec);

    // Temporary
    QSettingSection tempSection(SECTION_NAME_TEMP);
    QFileInfo tool1File(tool1Path), tool2File(tool2Path);
    if (tool1File.isFile()) {
        tempSection.addPair(KEY_NAME_TOOL1_PATH,
                            QDir::toNativeSeparators(tool1File.absoluteFilePath()));
    }
    if (tool2File.isFile()) {
        tempSection.addPair(KEY_NAME_TOOL2_PATH,
                            QDir::toNativeSeparators(tool2File.absoluteFilePath()));
    }

    // Insert Lyrics
    QString sInsertLyric;
    {
        QTextStream ts(&sInsertLyric);
        ts << ignoreRestsWhenInsert << "," << replaceLyricsWhenInsert << ","
           << separateCharWhenInsert;
    }
    tempSection.addPair(KEY_NAME_INSERT_LYRICS_STATE, sInsertLyric);
    setting.addSection(tempSection);

    // Projects
    QStringList fileList = projects.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_PROJECT, KEY_PREFIX_PROJECT,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Voice Banks
    fileList = folders.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_VOICE, KEY_PREFIX_VOICE,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Wavtools
    fileList = wavtools.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_WAVTOOL, KEY_PREFIX_WAVTOOL,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // Resamplers
    fileList = resamplers.valid();
    if (!fileList.isEmpty()) {
        setting.addArraySection(SECTION_NAME_RESAMPLER, KEY_PREFIX_RESAMPLER,
                                batchReplace(fileList, QDir::toNativeSeparators));
    }

    // GUI Section
    QSettingSection guiSection(SECTION_NAME_GUI);

    // Window
    QString sWindow;
    {
        QTextStream ts(&sWindow);
        ts << windowRect.x() << "," << windowRect.y() << "," << windowRect.width() << ","
           << windowRect.height() << "," << windowMaximized;
    }
    guiSection.addPair(KEY_NAME_MAINWINDOW, sWindow);

    // Quantization
    guiSection.addPair(KEY_NAME_LAST_QUANTIZE, lastQuantize);

    // Forms
    QString sFormVisible;
    {
        QTextStream ts(&sFormVisible);
        ts << tracksFormVisibility << "," << editorFormVisibility << "," << paramsFormVisibility;
    }
    guiSection.addPair(KEY_NAME_FORMS_VISIBILITY, sFormVisible);

    // Note, Pitch, Enevelope, Params
    QString sElements;
    {
        QTextStream ts(&sElements);
        ts << noteVisibility << "," << pitchVisibility << "," << envelopeVisibility << ","
           << paramsVisibility;
    }
    guiSection.addPair(KEY_NAME_ELEMENTS_STATE, sElements);

    // Playhead
    guiSection.addPair(KEY_NAME_PLAYHEAD_STATE, playHeadCenter ? 1 : 0);

    // Foreground
    QString sForeground;
    {
        QTextStream ts(&sForeground);
        ts << int(spriteOpacity * 100) << "," << spriteVisibility << "," << spritePosition;
    }
    guiSection.addPair(KEY_NAME_FOREGROUND_STATE, sForeground);

    // Theme Index
    guiSection.addPair(KEY_NAME_THEME_INDEX, themeIndex);

    setting.addSection(guiSection);

    return setting.save(m_filename);
}

void SettingIniFile::resetCore() {
    tool1Path = "";
    tool2Path = "";

    projects.clear();
    folders.clear();
    wavtools.clear();
    resamplers.clear();

    windowRect = NO_RECT;
    windowMaximized = false;

    tracksFormVisibility = true;
    editorFormVisibility = true;
    paramsFormVisibility = true;

    lastQuantize = 1;
    ignoreRestsWhenInsert = true;
    replaceLyricsWhenInsert = true;
    separateCharWhenInsert = false;

    noteVisibility = false;
    pitchVisibility = true;
    envelopeVisibility = true;
    paramsVisibility = true;

    playHeadCenter = false;

    spriteVisibility = false;
    spriteOpacity = 0.3;
    spritePosition = Qt::BottomRightCorner;

    themeIndex = 0;
}
