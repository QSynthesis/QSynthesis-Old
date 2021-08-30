#ifndef GRAPHICSNOTE_H
#define GRAPHICSNOTE_H

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMoveEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QVariant>

#include "Graphics/GraphicsDragger.h"
#include "GraphicsLines.h"
#include "Note/QLinkNote.h"
#include "QUtils.h"

#include "../Handlers/EnvelopeHandler.h"
#include "../Handlers/Mode2Handler.h"
#include "../Handlers/NoteHandler.h"

class NotesArea;
class GraphicsLifter;

class GraphicsNote : public GraphicsDragger {
public:
    explicit GraphicsNote(NotesArea *editor, QGraphicsItem *parent = nullptr);
    virtual ~GraphicsNote();

    QLinkNote Note;

    friend class DraggerHandler;

private:
    void init();

public:
    GraphicsNote *prev() const;
    void setPrev(GraphicsNote *prev);

    GraphicsNote *next() const;
    void setNext(GraphicsNote *next);

    GraphicsNote *MNext() const;
    void setMNext(GraphicsNote *MNext);

    GraphicsNote *MPrev() const;
    void setMPrev(GraphicsNote *MPrev);

    Mode2Handler *curves();
    EnvelopeHandler *envelope();
    NoteHandler *handler();

    GraphicsLifter *lifter();
    GraphicsLines *screen() const;

public:
    void setGeometry(QRectF geometry);
    void setGeometry(double x, double y, double w, double h);
    QRectF geometry() const;

    void setLocation(QPointF pos) override;
    void setSize(QSizeF size) override;

    void adjustSize(bool involve);
    void adjustComponents();

    void adjustCurves();
    void adjustEnvelope();
    void adjustLifter();

    void addLifter();
    void removeLifter();

    void addScreen();
    void removeScreen();

    // States
public:
    bool movable() const;
    void setMovable(bool movable);

    bool stretch() const;
    void setStretch(bool stretch);

    bool drawing() const;
    void setDrawing(bool drawing);

    // Values
public:
    QGenonSettings genonSettings() const;
    QCorrectGenon correctGenon() const;

    Qs::NoteStatus status() const;
    void setStatus(const Qs::NoteStatus &status);
    virtual void setSelected(bool selected) override;

    bool isRest() const;
    bool isListed() const;
    bool isUnisted() const;

    double time() const;
    void setTime(double time);

    int tick() const;
    void setTick(int tick);

    double tempo() const;
    void setTempo(double tempo);

    bool tempoEdited() const;

    double duration() const;

    double intensity() const;
    double modulation() const;
    double velocity() const;
    double startPoint() const;
    double preUtterance() const;
    double voiceOverlap() const;

    double inPoint() const;
    double outPoint() const;
    double inOverlapPoint() const;
    double outOverlapPoint() const;

    QPointF headPos() const;
    QPointF bodyPos() const;
    QPointF tailPos() const;

    // Assist
public:
    int convertTimeToTick(double time) const;
    double convertTickToTime(double tick) const;

    // Update
public:
    void updateNoteStatus();
    bool updateGenonSettings();
    void updateCorrectGenon();
    void updateNeighborCorrectGenons(bool update = false);

    void updateComponents(bool prev = true, bool curr = true, bool next = true);

private:
    NotesArea *m_editor;

    NoteHandler *m_handler;
    Mode2Handler *m_curves;
    EnvelopeHandler *m_envelope;

    GraphicsLifter *m_lifter;
    GraphicsLines *m_screen;

private:
    Qs::NoteStatus m_status;

    bool m_movable;
    bool m_stretch;
    bool m_drawing;

    GraphicsNote *m_prev, *m_next;   // Pointers of note right before and after
    GraphicsNote *m_MPrev, *m_MNext; // Reference for moving curves

private:
    QGenonSettings m_genonSettings; // Independent from Abstract note
    QCorrectGenon m_correctGenon;

    int m_tick;
    double m_time; // Time Cache
    double m_tempo;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

public:
    void afterPress();
    void afterMove(QPointF pos);
    void afterRelease(QPointF pos);

    // Link

protected:
    QPointF limitArea(QPointF p) override;
    QPointF limitAreaT(QPointF p) override;
    QSizeF limitSize(QSizeF s) override;

    void linkStretch(QPointF pos);

    void linkMove(QPointF pos) override;
    void involveMove(QPointF pos) override;

    virtual void handlePosChange() override;
    virtual void handleSizeChange() override;
};

#endif // GRAPHICSNOTE_H
