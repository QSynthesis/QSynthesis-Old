#ifndef QVOCALOIDFILE_H
#define QVOCALOIDFILE_H

#include <QObject>
#include <QXmlStreamReader>

// Vocaloid 工程文件解析
class QVocaloidFile {
public:
    enum Format {
        VSQ,
        VSQX,
    };
    QVocaloidFile(Format format);
    QVocaloidFile();

    Format format() const;
    void setFormat(const Format &format);

private:
    Format m_format;
};

#endif // QVOCALOIDFILE_H
