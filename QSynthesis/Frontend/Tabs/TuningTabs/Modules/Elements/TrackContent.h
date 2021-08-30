#ifndef TRACKCONTENT_H
#define TRACKCONTENT_H

#include <QDial>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "QUtils.h"
#include "Utils/ItemList.h"

class NotesArea;
class BlocksArea;
class GraphicsNote;

// Track Midi placeholder
class TrackContent : public QWidget {
    Q_OBJECT

    Q_PROPERTY(QColor midiColor READ midiColor WRITE setMidiColor NOTIFY colorChanged)
    Q_PROPERTY(QColor backColor READ backColor WRITE setBackColor NOTIFY colorChanged)

public:
    explicit TrackContent(ItemList<GraphicsNote> &notesList, BlocksArea *parent);
    ~TrackContent();

    void adjustWidth();

    void onLengthChanged();

    double sectionWidth() const;
    void setSectionWidth(double value);

    QColor midiColor() const;
    void setMidiColor(const QColor &midiColor);

    QColor backColor() const;
    void setBackColor(const QColor &backColor);

private:
    BlocksArea *m_parent;

    ItemList<GraphicsNote> &notesList;
    double m_width;

private:
    QColor m_midiColor;
    QColor m_backColor;

    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void colorChanged();
    void resized(QSize size);
    void moved(QPoint pos);
};

#endif // TRACKCONTENT_H
