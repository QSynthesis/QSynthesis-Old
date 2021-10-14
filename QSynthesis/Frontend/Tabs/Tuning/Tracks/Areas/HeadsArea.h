#ifndef HEADSAREA_H
#define HEADSAREA_H

#include <QVBoxLayout>

#include "Utils/ItemList.h"
#include "MoreWidget.h"

class TracksInterface;
class TuningGroup;
class GraphicsNote;
class TrackHead;
class TrackOperation;

class HeadsArea : public MoreWidget {
    Q_OBJECT
public:
    explicit HeadsArea(TracksInterface *editor,QWidget *parent = nullptr);
    virtual ~HeadsArea();

    TuningGroup *ptrs() const;

    void addTrack(const QString &resampler, const QString &flags, const QString &name,
                  const QString &voice);

    void setTrackResampler(int index, const QString &resampler);
    void setTrackFlags(int index, const QString &flags);
    void setTrackName(int index, const QString &name);
    void setTrackVoice(int index, const QString &voice);

    void setHeadsMode(int n);

    QList<TrackHead *> Tracks;

private:
    TuningGroup *m_ptrs;

private:
    QVBoxLayout *mainLayout;

    void handleNameChanged(QString orgVal, QString newVal);
    void handleFlagsChanged(QString orgVal, QString newVal);
    void handleVoiceChanged(QString orgVal, QString newVal);
    void handleResamplerChanged(QString orgVal, QString newVal);

public:
    void saveOperation(TrackOperation *t);
    bool handleOperation(TrackOperation *t, bool undo = true);

public:
    void reloadByVoice(const QString &voice);

signals:
    void nameChanged(int index, QString newVal);
    void flagsChanged(int index, QString newVal);

    void voiceChanged(int index, QString newVal);
    void resamplerChanged(int index, QString newVal);
};

#endif // HEADSAREA_H
