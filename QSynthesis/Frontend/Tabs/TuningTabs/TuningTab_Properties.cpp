#include "../TuningTab.h"

QString TuningTab::fullFileName() const {
    QString filename = m_filename;
    if (!filename.endsWith(".ust", Qt::CaseInsensitive)) {
        filename.append(".ust");
    }
    return filename;
}

bool TuningTab::isUntitled() const {
    return untitled;
}

void TuningTab::setUntitled(bool value) {
    untitled = value;
    updateTabName();
    updateMenuCore();
}

bool TuningTab::isDeleted() const {
    return deleted;
}

void TuningTab::setDeleted(bool value) {
    deleted = value;
    updateTabName();
    updateMenuCore();
}

QString TuningTab::workingDir() const {
    return m_workingDir;
}

QString TuningTab::defaultCacheDir() const {
    QFileInfo file(m_filename);
    if (file.isFile()) {
        QString absoluteFileName = file.absoluteFilePath();
        int dot = absoluteFileName.lastIndexOf('.');
        if (dot < 0) {
            dot = absoluteFileName.size();
        }
        return absoluteFileName.mid(0, dot) + ".cache";
    } else {
        return m_workingDir + Slash + DIR_NAME_TEMP_CACHE;
    }
}

QString TuningTab::relativeCacheDir() const {
    if (isFileExist(m_filename)) {
        return PathFindFileName(defaultCacheDir(), PathFindUpper(m_filename));
    } else {
        return "";
    }
}

QString TuningTab::tempAudioFile() const {
    return m_workingDir + Slash + FILE_NAME_TEMP_AUDIO;
}
