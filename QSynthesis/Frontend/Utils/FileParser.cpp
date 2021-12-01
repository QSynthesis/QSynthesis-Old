#include "FileParser.h"
#include "QUtauSections.h"
#include "QUtils.h"

FileParser::FileParser(QWidget *parent) : QObject(parent) {
}

FileParser::~FileParser() {
}

bool FileParser::parseFile(const QString &filename, SectionNotes &oNotes) {
    QString suffix = PathFindSuffix(filename).toLower();
    if (suffix == "mid") {
        SectionNotes notes;
        if (parseMidiFile(filename, notes)) {
            oNotes = notes;
            return true;
        }
    }
    return false;
}
