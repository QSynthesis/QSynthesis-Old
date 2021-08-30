#include "QUtauUtils.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"
#include "QUtils.h"

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

QVector<QString> qstring_to_qvector_qstring(const QString &oStr, const QString &oDelim) {
    QString::size_type aCurPos = 0, aNextPos;
    QVector<QString> aVectorString;

    aVectorString.clear();
    while (aCurPos < oStr.length()) {
        aNextPos = oStr.indexOf(oDelim, aCurPos);
        if (aNextPos < 0) {
            aNextPos = oStr.length();
        }
        aVectorString.push_back(oStr.mid(aCurPos, aNextPos - aCurPos));
        aCurPos = aNextPos + 1;
    }
    if (aVectorString.empty()) {
        aVectorString.push_back(NODEF_STRING);
    }
    return aVectorString;
}

QVector<int> qstring_to_qvector_int(const QString &oStr, const QString &oDelim) {
    QVector<QString> aVectorString = qstring_to_qvector_qstring(oStr, oDelim);
    QVector<int> aVectorInt32;

    for (QVector<QString>::size_type i = 0; i < aVectorString.size(); i++) {
        if (!aVectorString[i].isEmpty()) {
            aVectorInt32.push_back(aVectorString[i].toInt());
        } else {
            aVectorInt32.push_back(NODEF_INT);
        }
    }
    return aVectorInt32;
}

QVector<double> qstring_to_qvector_double(const QString &oStr, const QString &oDelim) {
    QVector<QString> aVectorString = qstring_to_qvector_qstring(oStr, oDelim);

    return qvector_qstring_to_qvector_double(aVectorString);
}

QVector<QString> qvector_double_to_qvector_qstring(const QVector<double> &oVectorDouble) {
    QVector<QString> aVectorString;

    for (QVector<QString>::size_type i = 0; i < oVectorDouble.size(); i++) {
        if (oVectorDouble[i] != NODEF_DOUBLE) {
            aVectorString.push_back(num_to_qstring(oVectorDouble[i]));
        } else {
            aVectorString.push_back(NODEF_STRING);
        }
    }
    return aVectorString;
}

QVector<double> qvector_qstring_to_qvector_double(const QVector<QString> &oVectorString) {
    QVector<double> aVectorDouble;

    for (QVector<QString>::size_type i = 0; i < oVectorString.size(); i++) {
        if (!oVectorString[i].isEmpty()) {
            aVectorDouble.push_back(oVectorString[i].toDouble());
        } else {
            aVectorDouble.push_back(NODEF_DOUBLE);
        }
    }
    return aVectorDouble;
}

QString qvector_qstring_to_qstring(const QVector<QString> &oVectorString, const QString &oDelim) {
    QString aStr;

    for (QVector<QString>::size_type i = 0; i < oVectorString.size(); i++) {
        if (oVectorString[i] != NODEF_STRING) {
            aStr += oVectorString[i];
        }
        if (i < oVectorString.size() - 1) {
            aStr += oDelim;
        }
    }
    return aStr;
}

QString qvector_int_to_qstring(const QVector<int> &oVectorInt32, const QString &oDelim) {
    QVector<QString> aVectorString;

    for (QVector<int>::size_type i = 0; i < oVectorInt32.size(); i++) {
        if (oVectorInt32[i] != NODEF_INT) {
            aVectorString.push_back(num_to_qstring(oVectorInt32[i]));
        } else {
            aVectorString.push_back(NODEF_STRING);
        }
    }
    return qvector_qstring_to_qstring(aVectorString, oDelim);
}

QString qvector_double_to_qstring(const QVector<double> &oVectorDouble, const QString &oDelim) {
    QVector<QString> aVectorString;

    aVectorString = qvector_double_to_qvector_qstring(oVectorDouble);
    return qvector_qstring_to_qstring(aVectorString, oDelim);
}

double tick_to_time(int oTick, double oTempo) {
    return (static_cast<unsigned long>(60000) * oTick) / (oTempo * TIME_BASE);
}

int time_to_tick(double oTime, double oTempo) {
    return static_cast<int>(oTime * oTempo * TIME_BASE / 60000);
}

int tone_name_to_tone_number(const QString &oToneName) {
    int aOctave;
    QString::size_type aToneNameIndex;

    if (oToneName.length() < 2) {
        return TONE_NUMBER_BASE;
    }

    aToneNameIndex = TONE_NAMES.indexOf(oToneName[0]);
    if (aToneNameIndex < 0) {
        aToneNameIndex = 0;
    }

    aOctave = oToneName.rightRef(1).toInt();

    if (aOctave < TONE_OCTAVE_MIN) {
        aOctave = TONE_OCTAVE_MIN;
    } else if (aOctave > TONE_OCTAVE_MAX) {
        aOctave = TONE_OCTAVE_MAX;
    }

    return TONE_NUMBER_BASE + (aOctave - 1) * TONE_OCTAVE_STEPS + aToneNameIndex +
           static_cast<int>(oToneName[1] == TONE_NAME_SHARP);
}

QString tone_number_to_tone_name(int oToneNumber) {
    return tone_number_to_tone_name(oToneNumber % TONE_OCTAVE_STEPS,
                                    oToneNumber / TONE_OCTAVE_STEPS - 2);
}

QString tone_number_to_tone_name(int oNameIndex, int oOctaveIndex) {
    QString aToneName;

    aToneName = TONE_NAMES[oNameIndex];
    if (oNameIndex > 0 && TONE_NAMES[oNameIndex] == TONE_NAMES[oNameIndex - 1]) {
        aToneName += TONE_NAME_SHARP;
    }
    aToneName += num_to_qstring(oOctaveIndex + 1);
    return aToneName;
}

int find_file(const QString &oBaseFolder, const QString &oLeaf, QStringList *oFiles) {
    if (oBaseFolder.isEmpty() || oLeaf.isEmpty()) {
        return 0;
    }

    QDir aDir;
    QStringList aFilters;
    QString aPath;

    aFilters << oLeaf;
    aDir.setPath(oBaseFolder);
    aDir.setNameFilters(aFilters);

    QDirIterator iter(aDir, QDirIterator::Subdirectories);

    while (iter.hasNext()) {
        iter.next();
        QFileInfo aInfo = iter.fileInfo();
        if (aInfo.isFile()) {
            aPath = aInfo.absoluteFilePath();
            aPath = QDir::toNativeSeparators(aPath); // 适配分隔符
            (*oFiles).append(aPath);
        }
    }

    return oFiles->size();
}

bool isRestNoteLyric(const QString &oLyric) {
    QString aTrimmedLyric = oLyric.trimmed();

    return (aTrimmedLyric.isEmpty() || aTrimmedLyric == "R" || aTrimmedLyric == "r");
}

QString GetInnerPath(QString filePath) {
    QString s1 = filePath.replace("%VOICE%", DIR_NAME_VOICE + Slash);
    if (isPathRelative(s1)) {
        s1 = AppPath + Slash + s1;
    }
    return s1;
}

QString fromUSTVoiceDir(QString filePath) {
    filePath = QDir::fromNativeSeparators(filePath);

    QString voice = AppPath + Slash + DIR_NAME_VOICE + Slash;
    int index = filePath.indexOf("%VOICE%");

    if (index >= 0) {
        filePath = filePath.replace("%VOICE%", voice);
    } else if (isPathRelative(filePath)) {
        filePath = AppPath + Slash + filePath;
    }

    return filePath;
}

QString toUSTVoiceDir(QString filePath) {
    QString voice = AppPath + Slash + DIR_NAME_VOICE + Slash;

    if (filePath.startsWith(voice)) {
        filePath = "%VOICE%" + PathFindFileName(filePath, voice);
    }

    filePath = QDir::toNativeSeparators(filePath);
    return filePath;
}

QString fromUSTToolsDir(QString filePath) {
    filePath = QDir::fromNativeSeparators(filePath);

    if (isPathRelative(filePath)) {
        filePath = AppPath + Slash + filePath;
    }
    return filePath;
}

QString toUSTToolsDir(QString filePath) {
    QString voice = AppPath + Slash;

    if (filePath.startsWith(voice)) {
        filePath = PathFindFileName(filePath, voice);
    }

    filePath = QDir::toNativeSeparators(filePath);
    return filePath;
}
