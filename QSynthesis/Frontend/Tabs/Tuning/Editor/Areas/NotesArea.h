#ifndef NOTESAREA_H
#define NOTESAREA_H

#include <QGraphicsSceneMoveEvent>
#include <QRubberBand>
#include <QWidget>

#include "../../Graphics/GraphicsBar.h"
#include "../../Graphics/GraphicsLifter.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/GraphicsPlayHead.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../Graphics/GraphicsRubber.h"
#include "../../Graphics/GraphicsSprite.h"
#include "Find/FindOption.h"
#include "Graphics/GraphicsArea.h"
#include "Graphics/GraphicsLineEdit.h"
#include "QUtauBasic.h"
#include "QUtauRender.h"
#include "QUtils.h"
#include "Transfer/NoteProperties.h"
#include "Transfer/NoteReadonlys.h"
#include "Transfer/PluginTempData.h"
#include "Utils/ItemList.h"

class EditorInterface;
class TuningGroup;
class NoteOperation;
class NotesScrollArea;

class NotesArea : public GraphicsArea {
    Q_OBJECT

public:
    explicit NotesArea(EditorInterface *editor, NotesScrollArea *view = nullptr);
    virtual ~NotesArea();

    NotesScrollArea *view() const;

    void updateColorTheme();

    TuningGroup *ptrs() const;

    ItemList<GraphicsNote> NotesList;

    const double spriteZIndex = 1;
    const double noteZIndex = 2;
    const double pointZIndex = 3;
    const double linesZIndex = 4;
    const double vibratoZIndex = 5;
    const double lyricEditZIndex = 6;
    const double rubberBandZIndex = 7;
    const double playHeadZIndex = 8;
    const double barZIndex = 9;

private:
    TuningGroup *m_ptrs;

    bool m_moving;

    GraphicsDragger *m_drawingItem;
    QPoint m_renderRange;

    double m_globalTempo;

    bool m_notesEnabled;
    bool m_pitchesEnabled;
    bool m_envelopesEnabled;

    bool m_notesVisible;
    bool m_pitchesVisible;
    bool m_envelopesVisible;
    bool m_paramsVisible;

    bool m_spriteVisible;
    Qt::Corner m_spritePosition;

    bool m_playHeadOnCenter;

    QColor m_quarterLineColor;
    QColor m_timeLineColor;
    QColor m_sectionLineColor;
    QColor m_pitchLineColor;
    QColor m_levelLineColor;
    QColor m_backDarkColor;
    QColor m_backLightColor;

public:
    void saveOperation(NoteOperation *n);                     // Out
    bool handleOperation(NoteOperation *o, bool undo = true); // In

private:
    void executeOperation(NoteOperation *n, bool undo);
    void removeCacheByOperation(NoteOperation *n, bool undo);

    // Call
public:
    void callForChange();
    void callForLengthen();
    void callForPlayback();

    double globalTempo() const;
    void setGlobalTempo(double globalTempo);

public:
    void adjustSize();
    void updateBackground();

    void centralizeVision(GraphicsNote *p, bool animate = false); // Move vision to fit note
    void centralizeVision(int index, bool animate = false);

    void selectNote(GraphicsNote *p, bool single = true);

    void moveToStart();
    void moveToEnd();

public:
    void adjustNotes(QPoint range = QPoint(-1, -1));
    void adjustNoteComponents(QPoint range = QPoint(-1, -1));

    QPoint selectContinuously(bool selectAll = false);
    QPoint selectRange(QPoint range);
    QPoint selectSequence(const QList<int> &indexs);

    // Actions
public:
    void autoDelete();
    void autoPaste(const QList<QLinkNote> &notes);

    void inputNotes(const QList<QLinkNote> &notes);

    void preparePlugin(PluginTempData &ns, bool all);
    void receivePlugin(const PluginTempData &ns, QPoint orgRegion);

    QList<RenderArgs> prepareRender();

    void removeSelectedNotes();
    void removeSelectedPoints();

    void shiftSelectedNotes(int offset);
    void modifySelectedNotes(const NoteProperties &orgValues, const NoteProperties &newValues);

    void insertLyrics(const QStringList &lyrics);
    void replaceSingleLyric(const QString &lyric, GraphicsNote *p);
    void replaceLyrics(const QList<int> &indexs, const QStringList &lyrics);
    void replaceSelectedLyrics(const QStringList &lyrics, bool ignoreRest);

    void insertRest();
    void removeRestLessThan(int len);
    void modifySelectedTempo(double tempo);

    void modifySelectedEnvelope(Qs::EnvelopeBatch method);

public:
    void pasteNotes(const QList<QLinkNote> &notes);
    void pasteMode2(const QList<QLinkNote> &notes);
    void pasteEnvelope(const QList<QLinkNote> &notes);

private:
    GraphicsNote *insertNote(int index, const QLinkNote &note);
    GraphicsNote *appendNote(const QLinkNote &note); // *!*

    GraphicsNote *insertNotes(const QList<int> &indexs, const QList<QLinkNote> &notes); // *!*

    void removeNote(int index);
    void removeNote(GraphicsNote *p);

    void removeNotes(const QList<int> &indexs); // *!*
    void clearNotes();                          // *!*
    void removeAllNotes();                      // *!*

    // Variate Move
private:
    void moveNotes(QPoint range, int movement);

    // Const
public:
    double zeroLine() const;

    bool isAvailableToPaste() const;

    QPoint continuousSelection() const;
    bool isSelectionContinuous() const;

    int totalLength() const;

    QList<QLinkNote> allNotes() const;
    QList<QLinkNote> selectedNotes() const;

    QList<RenderArgs> allRenderArgs() const;
    RenderArgs renderArgsAt(int index) const;
    QList<RenderArgs> renderArgsWithin(int x, int y) const;

    QList<NoteProperties> selectedProperties() const;

    int playToNote() const;
    double playToTick() const;

    // Draw
public:
    GraphicsNote *insertNoteFromCursor(QPointF pos);
    void prepareDrawNote(QGraphicsSceneMouseEvent *event);

    GraphicsPoint *insertPointFromCursor(QPointF pos);
    void prepareDrawPoint(QGraphicsSceneMouseEvent *event);

    void removePointFromCursor(GraphicsPoint *p);
    void changePointFromCursor(GraphicsPoint *p);

    void addPortamento(GraphicsNote *p);
    void removePortamento(GraphicsNote *p);

    void addVibrato(GraphicsNote *p);
    void removeVibrato(GraphicsNote *p);

    // Move
public:
    void prepareMove(GraphicsNote *p);
    void refreshMove(GraphicsNote *p);

    void endMove(GraphicsNote *p);
    void afterDraw(GraphicsNote *p);

    // Points Slots
    void prepareMove(GraphicsPoint *p);
    void refreshMove(GraphicsPoint *p, QPointF pos);

    void endMove(GraphicsPoint *p);
    void afterDraw(GraphicsPoint *p);

    void afterModifyVibrato(GraphicsNote *p);

    void afterModifyLifters(GraphicsLifter::Props prop);

    // States
public:
    bool isMoving() const;
    bool isSelecting() const;
    bool isLyricEditing() const;
    bool isPlaying() const;

    bool notesEnabled() const;
    bool pitchesEnabled() const;
    bool envelopesEnabled() const;

    bool notesVisible() const;
    bool pitchesVisible() const;
    bool envelopesVisible() const;
    bool paramsVisible() const;

    void setNotesEnabled(bool enabled);
    void setPitchesEnabled(bool enabled);
    void setEnvelopesEnabled(bool enabled);

    void setNotesVisible(bool visible);
    void setPitchesVisible(bool visible);
    void setEnvelopesVisible(bool visible);
    void setParamsVisible(bool visible);

    bool playHeadOnCenter() const;
    void setPlayHeadOnCenter(bool playHeadOnCenter);

    bool spriteVisible() const;
    void setSpriteVisible(bool visible);

    double spriteAlpha() const;
    void setSpriteAlpha(double alpha);

    Qt::Corner spritePosition() const;
    void setSpritePosition(Qt::Corner position);

    void setRenderRange(int x, int y);

    // Update
public:
    void updateNoteTickAfter(int index);
    void updateNoteTimeAfter(int index);
    int updateNoteTempoAfter(int index, bool br = false); // Return the next tempo-edited index

    void updateNotesStatus(QPoint range = QPoint(-1, -1));
    void updateNotesCorrectGeonon(QPoint range = QPoint(-1, -1));

    // Assist
public:
    double tempoAt(int index) const;

    bool getGenonSettings(QString lrc, QGenonSettings *genon, int noteNum) const;

    QPointF convertValueToPosition(int tick, int noteNum) const;
    QRectF convertValueToGeometry(int tick, int noteNum, int length) const;

    QPair<int, int> convertPositionToValue(QPointF pos) const;
    double convertWidthToLength(int width) const;

    double convertTickToTime(int tick) const;

    int findNoteAtPos(double x) const;
    int findNoteAtTick(int x) const;
    int findNoteAtTime(double x) const;
    int findNoteAtPosAbs(double x) const;

    QPoint viewportNotesRange() const;

    QRectF viewportRect() const;

    // Core
private:
    GraphicsNote *createNoteCore(const QLinkNote &note);
    void removeNoteCore(GraphicsNote *p);

    void savePointsCore(const ItemList<ScopeHandler> &list, bool mode2);
    void saveScatterCore(const ItemList<Mode2Handler> &list, bool vbr);

    QList<RenderArgs> getRenderArgsCore(QPoint range) const;

    // Lyric
private:
    GraphicsLineEdit *m_lyricEdit;
    GraphicsNote *m_curEditNote;

    void initLyricModules();

    void setCurEditNote(GraphicsNote *p);

    void editFinish();
    void editNextLyric();

    void switchLyric();
    void abandonLyric();

public:
    void editNoteLyric(GraphicsNote *pNote);
    void endEditingNote();

    GraphicsNote *curEditNote() const;

    // Select
private:
    GraphicsRubber *m_selector; // Frame Selector
    bool m_selecting;

    void initSelectModules();

    void startSelecting(bool vertical = false);
    void duringSelecting();
    void stopSelecting();

    void analyseSelect();

    // Find
private:
    FindOption m_findOption;
    bool m_finding;

    void updateFindStatus();
    void updateFindStatusAt(int index);
    void updateNoteFindStatus(GraphicsNote *p);
    void updateFindIndexs();

public:
    bool finding() const;
    void setFinding(bool finding);

    FindOption findOption() const;
    void setFindOption(const FindOption &opt);

    void findAtIndex(int index);

    void replaceByFind(const ReplaceOption &opt, bool all);

    // Play
private:
    GraphicsPlayHead *playHead;
    int m_playToNote;
    qint64 m_playToPosition;
    double m_playToTick;

    void initPlayModules();

    void adjustPlayHead();
    void advancePlayHead();

public:
    void advancePlaying(qint64 position);
    void stopPlaying();

    void setPlayPosition(double x);

    // Sprite
private:
    GraphicsSprite *sprite;

    void initSpriteModules();
    void updateSprite();
    void updateSpriteVisibility();

public:
    void reloadSprite();

    // Bar
private:
    GraphicsBar *bar;

    void initBarModules();
    void updateBar();

public:
    void reloadBar();

    // Events
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void moveEvent(QGraphicsSceneMoveEvent *event) override;
    void resizeEvent(QGraphicsSceneResizeEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void handleSceneRectChanged(const QRectF &rect);
};

#endif // NOTESAREA_H
