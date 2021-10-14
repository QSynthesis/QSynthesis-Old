#ifndef PROJECTINFOHANDLER_H
#define PROJECTINFOHANDLER_H

#include <QObject>

class ProjectOperation;
class TuningTab;

class ProjectInfoHandler : public QObject {
    Q_OBJECT
public:
    explicit ProjectInfoHandler(TuningTab *parent = nullptr);
    ~ProjectInfoHandler();

    QString wavtool() const;
    void setWavtool(const QString &wavtool);

    QString outFile() const;
    void setOutFile(const QString &outFile);

    void modifyValues(const QString &wavtool, const QString &outFile);

private:
    TuningTab *m_tab;

    QString m_wavtool;
    QString m_outFile;

public:
    void saveOperation(ProjectOperation *p);
    bool handleOperation(ProjectOperation *p, bool undo = true);

signals:
};

#endif // PROJECTINFOHANDLER_H
