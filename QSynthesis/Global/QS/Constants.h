#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QRectF>
#include <QString>

const QString Version = "0.1.86";
const QString TempDirName = "QSyntehsis_Temporary";

const int SampleRate = 44100;
const int SampleBits = 16;
const int Channels = 1;

const QRect NO_RECT = QRect(0, 0, 0, 0);
const QRectF NO_RECTF = QRectF(0, 0, 0, 0);

const QString CLIPBOARD_FORMAT_NAME_NOTE = "qsynthesis/notes";

#endif // CONSTANTS_H
