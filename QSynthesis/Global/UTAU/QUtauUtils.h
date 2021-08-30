#ifndef QUTAUUTILS_H
#define QUTAUUTILS_H

#include <QVector>

#define num_to_qstring(x) QString::number(x)

QVector<QString> qstring_to_qvector_qstring(const QString &oStr, const QString &oDelim = ",");
QVector<int> qstring_to_qvector_int(const QString &oStr, const QString &oDelim = ",");
QVector<double> qstring_to_qvector_double(const QString &oStr, const QString &oDelim = ",");

QVector<QString> qvector_double_to_qvector_qstring(const QVector<double> &oVectorDouble);
QVector<double> qvector_qstring_to_qvector_double(const QVector<QString> &oVectorString);

QString qvector_qstring_to_qstring(const QVector<QString> &oVectorString,
                                   const QString &oDelim = ",");
QString qvector_int_to_qstring(const QVector<int> &oVectorInt32, const QString &oDelim = ",");
QString qvector_double_to_qstring(const QVector<double> &oVectorDouble,
                                  const QString &oDelim = ",");

double tick_to_time(int oTick, double oTempo);
int time_to_tick(double oTime, double oTempo);

int tone_name_to_tone_number(const QString &oToneName);
QString tone_number_to_tone_name(int oToneNumber);
QString tone_number_to_tone_name(int oNameIndex, int oOctaveIndex);

int find_file(const QString &oBaseFolder, const QString &oLeaf, QStringList *oFiles);

bool isRestNoteLyric(const QString &oLyric);

QString fromUSTVoiceDir(QString filePath);

QString toUSTVoiceDir(QString filePath);

QString fromUSTToolsDir(QString filePath);

QString toUSTToolsDir(QString filePath);

#endif // QUTAUUTILS_H
