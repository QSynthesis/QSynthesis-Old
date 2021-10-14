#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QMessageBox>
#include <QWidget>

class SectionNotes;

class FileParser : public QObject {
    Q_OBJECT
public:
    explicit FileParser(QWidget *parent = nullptr);
    ~FileParser();

    bool parseFile(const QString &filename, SectionNotes &oNotes);

private:
    bool parseMidiFile(const QString &filename, SectionNotes &oNotes);
    bool parseSynthVFile(const QString &filename, bool svp, SectionNotes &oNotes);
    bool parseVocaloidFile(const QString &filename, bool vsqx, SectionNotes &oNotes);

signals:
};

#endif // FILEPARSER_H
