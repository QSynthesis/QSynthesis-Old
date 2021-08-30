#ifndef BLOCKSAREA_H
#define BLOCKSAREA_H

#include <QVBoxLayout>
#include <QWidget>

#include "Utils/ItemList.h"

class TracksInterface;
class TuningGroup;
class TrackContent;
class GraphicsNote;

class BlocksArea : public QWidget {
    Q_OBJECT
public:
    explicit BlocksArea(TracksInterface *editor, QWidget *parent = nullptr);
    virtual ~BlocksArea();

    TuningGroup *ptrs() const;

    void addTrack(ItemList<GraphicsNote> &notes);
    void adjustTrack(int n);

    QList<TrackContent *> Tracks;

public:
    double sectionWidth() const;
    void setSectionWidth(double width);

private:
    TuningGroup *m_ptrs;

    QVBoxLayout *mainLayout;

    double m_width;
};

#endif // BLOCKSAREA_H
