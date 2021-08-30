#ifndef NOTEHANDLER_H
#define NOTEHANDLER_H

#include <QAction>
#include <QColor>
#include <QMenu>
#include <QObject>
#include <QPainter>
#include <QStyle>

#include "QUtils.h"

class GraphicsNote;
class NotesArea;

class NoteHandler : public QObject {
    Q_OBJECT
public:
    explicit NoteHandler();
    explicit NoteHandler(GraphicsNote *note, NotesArea *editor);
    ~NoteHandler();

private:
    void init();

public:
    GraphicsNote *note() const;
    void setNote(GraphicsNote *note);

    NotesArea *editor() const;
    void setEditor(NotesArea *editor);

public:
    void update();

public:
    QColor lyricColor() const;
    void setLyricColor(const QColor &lyricColor);

    QColor restFillColor() const;
    void setRestFillColor(const QColor &restFillColor);

    QColor restLineColor() const;
    void setRestLineColor(const QColor &restLineColor);

    QColor listedFillColor() const;
    void setListedFillColor(const QColor &listedFillColor);

    QColor listedLineColor() const;
    void setListedLineColor(const QColor &listedLineColor);

    QColor unlistedFillColor() const;
    void setUnlistedFillColor(const QColor &unlistedFillColor);

    QColor unlistedLineColor() const;
    void setUnlistedLineColor(const QColor &unlistedLineColor);

private:
    QColor m_lyricColor;

    QColor m_restFillColor;
    QColor m_restLineColor;

    QColor m_listedFillColor;
    QColor m_listedLineColor;

    QColor m_unlistedFillColor;
    QColor m_unlistedLineColor;

    GraphicsNote *m_note;
    NotesArea *m_editor;

public:
    void drawNote(QPainter *painter);

public:
    void openContextMenu();

private:
    void handlePortamentoTriggered(bool checked);
    void handleVibratoTriggered(bool checked);
    void handleVibratoEditorTriggered(bool checked);
    void handlePropertyTriggered();
    void handleLyricConfigTriggered();

public:
    void handleTempoTriggered();
    void handleRemoveTempoTriggered();

signals:
    void colorChanged();
};

#endif // NOTEHANDLER_H
