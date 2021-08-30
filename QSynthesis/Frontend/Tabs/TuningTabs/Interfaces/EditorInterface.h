#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

#include <QGraphicsView>
#include <QGridLayout>
#include <QScrollArea>

#include "BaseInterface.h"
#include "QUtils.h"

class SectionsArea;
class PianoArea;
class NotesArea;
class EditorForm;
class TuningGroup;
class NotesScrollArea;
class NoneScrollArea;

class EditorInterface : public BaseInterface {
    Q_OBJECT
public:
    explicit EditorInterface(EditorForm *parent = nullptr);
    virtual ~EditorInterface();

public:
    void setVisionStatus(Qs::Panels::Editor mode);

    TuningGroup *ptrs() const;

private:
    QGridLayout *mainLayout;

    NoneScrollArea *sectionsScroll;
    NoneScrollArea *pianoScroll;
    NotesScrollArea *notesScroll;

    SectionsArea *sectionsArea;
    NotesArea *notesArea;
    PianoArea *pianoArea;

    TuningGroup *m_ptrs;

    // Call
public:
    void adjustCanvas(int totalLength);

private:
    void wheelEvent(QWheelEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    // Link
private:
    void zoomHorizontally(int delta);
    void zoomVertically(int delta);

    void moveHorizontally(int delta);
    void moveVertically(int delta);

private:
    void handleHorizontalMove(int value);
    void handleVerticalMove(int value);
};

#endif // EDITORINTERFACE_H
