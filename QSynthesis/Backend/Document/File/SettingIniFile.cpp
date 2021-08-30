#include "SettingIniFile.h"
#include "UTAU/Strings/UtaSettingText.h"

using namespace UtaSettingText;

SettingIniFile::SettingIniFile(QObject *parent) : FileManager(parent) {
    reset();
}

SettingIniFile::SettingIniFile(const QString &filename, QObject *parent) : FileManager(parent) {
    setFilename(filename);
}

SettingIniFile::~SettingIniFile() {
}

bool SettingIniFile::loadCore(bool *valid) {
    QFile file(m_filename);
    if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QTextStream in(&file);
    QString line;
    int eq;

    QString key, value;
    int valueInt;
    bool isInt;

    while (!in.atEnd()) {
        line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }
        eq = line.indexOf("=");
        if (eq <= 0) {
            continue;
        }

        key = line.left(eq);
        value = line.mid(eq + 1);

        valueInt = value.toInt(&isInt);

        if (key == KEY_NAME_CACHE_ENABLE && isInt) {
            m_data.cacheEnable = valueInt != 0;
        } else if (key == KEY_NAME_CACHE_DELETE_BY_SIZE && isInt) {
            m_data.cacheDeleteBySize = valueInt != 0;
        } else if (key == KEY_NAME_CACHE_DELETE_SIZE && isInt) {
            m_data.cacheDeleteSize = valueInt;
        } else if (key == KEY_NAME_NO_OTO_REPORT && isInt) {
            m_data.noOtoReport = valueInt != 0;
        } else if (key == KEY_NAME_NO_COPY_GENON && isInt) {
            m_data.noCopyGenon = valueInt != 0;
        } else if (key == KEY_NAME_NO_BATCH_MODE && isInt) {
            m_data.noBatchMode = valueInt != 0;
        } else if (key == KEY_NAME_PROCESSES && isInt) {
            m_data.threadNumber = valueInt;
        } else if (key == KEY_NAME_TOOL1_PATH) {
            m_data.tool1Path = QDir::fromNativeSeparators(value);
        } else if (key == KEY_NAME_TOOL2_PATH) {
            m_data.tool2Path = QDir::fromNativeSeparators(value);
        } else if (key.startsWith(KEY_PREFIX_PROJECT)) {
            m_data.projects.push(QDir::fromNativeSeparators(value));
        } else if (key.startsWith(KEY_PREFIX_VOICE)) {
            m_data.folders.push(QDir::fromNativeSeparators(value));
        } else if (key.startsWith(KEY_PREFIX_WAVTOOL)) {
            m_data.wavtools.push(QDir::fromNativeSeparators(value));
        } else if (key.startsWith(KEY_PREFIX_RESAMPLER)) {
            m_data.resamplers.push(QDir::fromNativeSeparators(value));
        } else if (key.startsWith(KEY_NAME_MAINWINDOW)) {
            QStringList list = value.split(",");
            if (list.size() > 0) {
                m_data.windowRect.setX(list[0].toInt());
            }
            if (list.size() > 1) {
                m_data.windowRect.setY(list[1].toInt());
            }
            if (list.size() > 2) {
                m_data.windowRect.setWidth(list[2].toInt());
            }
            if (list.size() > 3) {
                m_data.windowRect.setHeight(list[3].toInt());
            }
            if (list.size() > 4) {
                m_data.windowMaximized = list[4].toInt();
            }
        }
    }

    file.close();
    return true;
}

bool SettingIniFile::saveCore() {
    QFile file(m_filename);
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        return 0;
    }

    QTextStream out(&file);

    out << "[" << SECTION_NAME_TEMP << "]" << Qt::endl;

    // Write two tools
    QFileInfo tool1File(m_data.tool1Path), tool2File(m_data.tool2Path);
    if (tool1File.isFile()) {
        out << QDir::toNativeSeparators(tool1File.absoluteFilePath()) << Qt::endl;
    }
    if (tool2File.isFile()) {
        out << QDir::toNativeSeparators(tool2File.absoluteFilePath()) << Qt::endl;
    }

    // Whether to process cache
    out << KEY_NAME_CACHE_ENABLE << "=" << QString::number(m_data.cacheEnable ? 1 : 0) << Qt::endl;

    // Whether to remove cache
    if (m_data.cacheEnable && m_data.cacheDeleteBySize) {
        out << KEY_NAME_CACHE_DELETE_BY_SIZE << "="
            << QString::number(m_data.cacheDeleteBySize ? 1 : 0) << Qt::endl;
        out << KEY_NAME_CACHE_DELETE_SIZE << "=" << QString::number(m_data.cacheDeleteSize)
            << Qt::endl;
    }

    // Whether to report oto warnings
    if (m_data.noOtoReport) {
        out << KEY_NAME_NO_OTO_REPORT << "=" << QString::number(m_data.noOtoReport ? 1 : 0)
            << Qt::endl;
    }

    // Whether to preserve pre-uttr and overlap when modifying lyrics
    if (!m_data.noCopyGenon) {
        out << KEY_NAME_NO_COPY_GENON << "=" << QString::number(m_data.noCopyGenon ? 1 : 0)
            << Qt::endl;
    }

    // Whether not to use batch processing
    if (m_data.noBatchMode && m_data.threadNumber) {
        out << KEY_NAME_NO_BATCH_MODE << "=" << QString::number(m_data.noBatchMode ? 1 : 0)
            << Qt::endl;
        out << KEY_NAME_PROCESSES << "=" << m_data.threadNumber << Qt::endl;
    }

    QStringList fileList = m_data.projects.valid();
    int count = 0;
    if (!fileList.isEmpty()) {
        out << "[" << SECTION_NAME_PROJECT << "]" << Qt::endl;
        for (auto it = fileList.begin(); it != fileList.end(); ++it) {
            ++count;
            out << KEY_PREFIX_PROJECT << QString::number(count) << "="
                << QDir::toNativeSeparators(*it) << Qt::endl;
        }
    }

    fileList = m_data.folders.valid();
    count = 0;
    if (!fileList.isEmpty()) {
        out << "[" << SECTION_NAME_VOICE << "]" << Qt::endl;
        for (auto it = fileList.begin(); it != fileList.end(); ++it) {
            ++count;
            out << KEY_PREFIX_VOICE << QString::number(count) << "="
                << QDir::toNativeSeparators(*it) << Qt::endl;
        }
    }

    fileList = m_data.wavtools.valid();
    count = 0;
    if (!fileList.isEmpty()) {
        out << "[" << SECTION_NAME_WAVTOOL << "]" << Qt::endl;
        for (auto it = fileList.begin(); it != fileList.end(); ++it) {
            ++count;
            out << KEY_PREFIX_WAVTOOL << QString::number(count) << "="
                << QDir::toNativeSeparators(*it) << Qt::endl;
        }
    }

    fileList = m_data.resamplers.valid();
    count = 0;
    if (!fileList.isEmpty()) {
        out << "[" << SECTION_NAME_RESAMPLER << "]" << Qt::endl;
        for (auto it = fileList.begin(); it != fileList.end(); ++it) {
            ++count;
            out << KEY_PREFIX_RESAMPLER << QString::number(count) << "="
                << QDir::toNativeSeparators(*it) << Qt::endl;
        }
    }

    // Main window coordinates
    out << "[" << SECTION_NAME_GUI << "]" << Qt::endl;
    out << KEY_NAME_MAINWINDOW << "=" << m_data.windowRect.x() << "," << m_data.windowRect.y()
        << "," << m_data.windowRect.width() << "," << m_data.windowRect.height() << ","
        << m_data.windowMaximized << Qt::endl;

    file.close();
    return true;
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
