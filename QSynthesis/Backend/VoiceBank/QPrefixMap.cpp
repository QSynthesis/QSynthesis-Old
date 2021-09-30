#include "QPrefixMap.h"
#include "Files/NormalFile.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"
#include "Utils/CharsetHandler.h"

Q_CHARSET_DECLARE(QPrefixMap)

QPrefixMap::QPrefixMap() : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
    reset();
}

QPrefixMap::QPrefixMap(const QString &filename) : BaseDirInfo(Qs::Default) {
    m_codec = defaultCodec;
    setDirname(filename);
}

QPrefixMap::~QPrefixMap() {
}

QString QPrefixMap::prefixedLyric(int oNoteNum, const QString &oLyric) const {
    QMap<int, QString>::const_iterator p;
    QString aPrefixedLyric = oLyric;

    p = PrefixMap.find(oNoteNum);
    if (p != PrefixMap.end()) {
        aPrefixedLyric = p.value() + aPrefixedLyric;
    }
    p = SuffixMap.find(oNoteNum);
    if (p != SuffixMap.end()) {
        aPrefixedLyric += p.value();
    }
    return aPrefixedLyric;
}

bool QPrefixMap::isEmpty() const {
    bool res = true;
    for (auto it = PrefixMap.begin(); it != PrefixMap.end(); ++it) {
        if (!it.value().isEmpty()) {
            res = false;
            break;
        }
    }
    if (!res) {
        return false;
    }
    for (auto it = SuffixMap.begin(); it != SuffixMap.end(); ++it) {
        if (!it.value().isEmpty()) {
            res = false;
            break;
        }
    }
    return res;
}

bool QPrefixMap::fromLocalFile(const QString &filename) {
    NormalFile file(filename);
    if (!file.exists()) {
        return true;
    }
    if (!file.load()) {
        return false;
    }

    int min = TONE_NUMBER_BASE;
    int max = min + (TONE_OCTAVE_MAX - TONE_OCTAVE_MIN + 1) * TONE_OCTAVE_STEPS - 1;

    QByteArray data = file.data();

    // Detect Code
    QString charset = CharsetHandler::detectCharset(data);
    QTextStream in(&data);

    if (!charset.isEmpty()) {
        m_codec = QTextCodec::codecForName(charset.toLatin1());
    }

    in.setCodec(m_codec);

    QString line;
    QVector<QString> lineStrings;

    while (!in.atEnd()) {
        line = in.readLine();
        if (!line.isEmpty()) {
            lineStrings = qstring_to_qvector_qstring(line, "\t");
            if (lineStrings.size() >= 3) {
                int noteNum = tone_name_to_tone_number(lineStrings[0]);
                if (noteNum >= min && noteNum <= max) {
                    PrefixMap[noteNum] = lineStrings[1];
                    SuffixMap[noteNum] = lineStrings[2];
                }
            }
        }
    }
    return true;
}

bool QPrefixMap::toLocalFile(const QString &filename) {
    NormalFile file(filename);

    // Delete when empty
    if (isEmpty()) {
        if (file.exists()) {
            return file.remove();
        } else {
            return true;
        }
    }

    QByteArray data;
    QTextStream out(&data);
    out.setCodec(m_codec);

    for (auto it = PrefixMap.begin(); it != PrefixMap.end(); ++it) {
        int key = it.key();
        out << tone_number_to_tone_name(key) << '\t';
        out << PrefixMap[key] << "\t";
        out << SuffixMap[key] << Qt::endl;
    }

    file.setData(data);
    return file.save();
}

bool QPrefixMap::loadCore(bool *valid) {
    return fromLocalFile(filename());
}

bool QPrefixMap::saveCore() {
    return toLocalFile(filename());
}

void QPrefixMap::resetCore() {
    int min = TONE_NUMBER_BASE;
    int max = min + (TONE_OCTAVE_MAX - TONE_OCTAVE_MIN + 1) * TONE_OCTAVE_STEPS - 1;
    for (int i = min; i <= max; ++i) {
        PrefixMap[i] = "";
        SuffixMap[i] = "";
    }
}

QString QPrefixMap::infoFilename() const {
    return FILE_NAME_PREFIX_MAP;
}
