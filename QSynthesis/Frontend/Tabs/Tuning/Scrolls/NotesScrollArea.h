#ifndef NOTESSCROLLAREA_H
#define NOTESSCROLLAREA_H

#include <QMenu>

#include "../Editor/Modules/FindReplaceDialog.h"
#include "../Editor/Modules/SpriteAdjustDialog.h"
#include "Graphics/GraphicsBaseView.h"

class NotesArea;

class NotesScrollArea : public GraphicsBaseView {
    Q_OBJECT

    Q_PROPERTY(QColor editorQuarterLine READ editorQuarterLine WRITE setEditorQuarterLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor editorTimeLine READ editorTimeLine WRITE setEditorTimeLine NOTIFY themeUpdated)
    Q_PROPERTY(QColor editorSectionLine READ editorSectionLine WRITE setEditorSectionLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor editorPitchLine READ editorPitchLine WRITE setEditorPitchLine NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor editorLevelLine READ editorLevelLine WRITE setEditorLevelLine NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor editorBackDark READ editorBackDark WRITE setEditorBackDark NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor editorBackLight READ editorBackLight WRITE setEditorBackLight NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor editorPlayHead READ editorPlayHead WRITE setEditorPlayHead NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode1SolidLineEnabled READ mode1SolidLineEnabled WRITE
                   setMode1SolidLineEnabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode1SolidLineDisabled READ mode1SolidLineDisabled WRITE
                   setMode1SolidLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode1DashLineEnabled READ mode1DashLineEnabled WRITE setMode1DashLineEnabled
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode1DashLineDisabled READ mode1DashLineDisabled WRITE
                   setMode1DashLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2SolidLineEnabled READ mode2SolidLineEnabled WRITE
                   setMode2SolidLineEnabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2SolidLineDisabled READ mode2SolidLineDisabled WRITE
                   setMode2SolidLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2DashLineEnabled READ mode2DashLineEnabled WRITE setMode2DashLineEnabled
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2DashLineDisabled READ mode2DashLineDisabled WRITE
                   setMode2DashLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2InvalidLineEnabled READ mode2InvalidLineEnabled WRITE
                   setMode2InvalidLineEnabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor mode2InvalidLineDisabled READ mode2InvalidLineDisabled WRITE
                   setMode2InvalidLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor mode2PointCore READ mode2PointCore WRITE setMode2PointCore NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor mode2PointRing READ mode2PointRing WRITE setMode2PointRing NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor vbrCurvesEnabled READ vbrCurvesEnabled WRITE setVbrCurvesEnabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor vbrCurvesDisabled READ vbrCurvesDisabled WRITE setVbrCurvesDisabled NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor vbrEditorLines READ vbrEditorLines WRITE setVbrEditorLines NOTIFY themeUpdated)
    Q_PROPERTY(QColor vbrPlaneHandleBorder READ vbrPlaneHandleBorder WRITE setVbrPlaneHandleBorder
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor vbrPlaneHandleFill READ vbrPlaneHandleFill WRITE setVbrPlaneHandleFill NOTIFY
                   themeUpdated)
    Q_PROPERTY(QColor vbrPlaneHandleText READ vbrPlaneHandleText WRITE setVbrPlaneHandleText NOTIFY
                   themeUpdated)
    Q_PROPERTY(QColor envSolidLineEnabled READ envSolidLineEnabled WRITE setEnvSolidLineEnabled
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor envSolidLineDisabled READ envSolidLineDisabled WRITE setEnvSolidLineDisabled
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor envDashLineEnabled READ envDashLineEnabled WRITE setEnvDashLineEnabled NOTIFY
                   themeUpdated)
    Q_PROPERTY(QColor envDashLineDisabled READ envDashLineDisabled WRITE setEnvDashLineDisabled
                   NOTIFY themeUpdated)
    Q_PROPERTY(QColor envInvalidLineEnabled READ envInvalidLineEnabled WRITE
                   setEnvInvalidLineEnabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor envInvalidLineDisabled READ envInvalidLineDisabled WRITE
                   setEnvInvalidLineDisabled NOTIFY themeUpdated)
    Q_PROPERTY(QColor envPointCore READ envPointCore WRITE setEnvPointCore NOTIFY themeUpdated)
    Q_PROPERTY(QColor envPointRing READ envPointRing WRITE setEnvPointRing NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteLyric READ noteLyric WRITE setNoteLyric NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteRestFill READ noteRestFill WRITE setNoteRestFill NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteRestLine READ noteRestLine WRITE setNoteRestLine NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor noteListedFill READ noteListedFill WRITE setNoteListedFill NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor noteListedLine READ noteListedLine WRITE setNoteListedLine NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor noteUnlistedFill READ noteUnlistedFill WRITE setNoteUnlistedFill NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor noteUnlistedLine READ noteUnlistedLine WRITE setNoteUnlistedLine NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteSelect READ noteSelect WRITE setNoteSelect NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor noteLyricBlock READ noteLyricBlock WRITE setNoteLyricBlock NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteHighlight READ noteHighlight WRITE setNoteHighlight NOTIFY themeUpdated)
    Q_PROPERTY(QColor noteParams READ noteParams WRITE setNoteParams NOTIFY themeUpdated)
    Q_PROPERTY(QColor rubberFrame READ rubberFrame WRITE setRubberFrame NOTIFY themeUpdated)
    Q_PROPERTY(QColor rubberFill READ rubberFill WRITE setRubberFill NOTIFY themeUpdated)

public:
    explicit NotesScrollArea(QWidget *parent = nullptr);
    virtual ~NotesScrollArea();

    friend class EditorInterface;

public:
    void setAdjusterVisible(bool visible);
    bool adjusterVisible() const;

    void setFinderVisible(bool visible);
    bool finderVisible() const;

    void updateFinderCaption(int cur, int total);

    NotesArea *scene() const;

private:
    SpriteAdjustDialog *adjuster;
    FindReplaceDialog *finder;

    void adjustModules();

    void handleVisibilityChanged(bool visible);
    void handleAlphaChanged(int alpha);
    void handleCornerChanged(Qt::Corner corner);
    void handleAdjusterCloseRequested();

    void handleFindStateChanged();
    void handleFindPrevRequested();
    void handleFindNextRequested();
    void handleReplaceRequested();
    void handleReplaceAllRequested();
    void handleFinderCloseRequested();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    void initLight();
    void initDark();

    // Color Theme
public:
    QColor editorQuarterLine() const;
    QColor editorTimeLine() const;
    QColor editorSectionLine() const;
    QColor editorPitchLine() const;
    QColor editorLevelLine() const;
    QColor editorBackDark() const;
    QColor editorBackLight() const;
    QColor editorPlayHead() const;

    QColor mode1SolidLineEnabled() const;
    QColor mode1SolidLineDisabled() const;
    QColor mode1DashLineEnabled() const;
    QColor mode1DashLineDisabled() const;

    QColor mode2SolidLineEnabled() const;
    QColor mode2SolidLineDisabled() const;
    QColor mode2DashLineEnabled() const;
    QColor mode2DashLineDisabled() const;
    QColor mode2InvalidLineEnabled() const;
    QColor mode2InvalidLineDisabled() const;
    QColor mode2PointCore() const;
    QColor mode2PointRing() const;

    QColor vbrCurvesEnabled() const;
    QColor vbrCurvesDisabled() const;
    QColor vbrEditorLines() const;
    QColor vbrPlaneHandleBorder() const;
    QColor vbrPlaneHandleFill() const;
    QColor vbrPlaneHandleText() const;

    QColor envSolidLineEnabled() const;
    QColor envSolidLineDisabled() const;
    QColor envDashLineEnabled() const;
    QColor envDashLineDisabled() const;
    QColor envInvalidLineEnabled() const;
    QColor envInvalidLineDisabled() const;
    QColor envPointCore() const;
    QColor envPointRing() const;

    QColor noteLyric() const;
    QColor noteRestFill() const;
    QColor noteRestLine() const;
    QColor noteListedFill() const;
    QColor noteListedLine() const;
    QColor noteUnlistedFill() const;
    QColor noteUnlistedLine() const;
    QColor noteSelect() const;
    QColor noteLyricBlock() const;
    QColor noteParams() const;
    QColor noteHighlight() const;

    QColor rubberFrame() const;
    QColor rubberFill() const;

    void setEditorQuarterLine(const QColor &color);
    void setEditorTimeLine(const QColor &color);
    void setEditorSectionLine(const QColor &color);
    void setEditorPitchLine(const QColor &color);
    void setEditorLevelLine(const QColor &color);
    void setEditorBackDark(const QColor &color);
    void setEditorBackLight(const QColor &color);
    void setEditorPlayHead(const QColor &color);

    void setMode1SolidLineEnabled(const QColor &color);
    void setMode1SolidLineDisabled(const QColor &color);
    void setMode1DashLineEnabled(const QColor &color);
    void setMode1DashLineDisabled(const QColor &color);

    void setMode2SolidLineEnabled(const QColor &color);
    void setMode2SolidLineDisabled(const QColor &color);
    void setMode2DashLineEnabled(const QColor &color);
    void setMode2DashLineDisabled(const QColor &color);
    void setMode2InvalidLineEnabled(const QColor &color);
    void setMode2InvalidLineDisabled(const QColor &color);
    void setMode2PointCore(const QColor &color);
    void setMode2PointRing(const QColor &color);

    void setVbrCurvesEnabled(const QColor &color);
    void setVbrCurvesDisabled(const QColor &color);
    void setVbrEditorLines(const QColor &color);
    void setVbrPlaneHandleBorder(const QColor &color);
    void setVbrPlaneHandleFill(const QColor &color);
    void setVbrPlaneHandleText(const QColor &color);

    void setEnvSolidLineEnabled(const QColor &color);
    void setEnvSolidLineDisabled(const QColor &color);
    void setEnvDashLineEnabled(const QColor &color);
    void setEnvDashLineDisabled(const QColor &color);
    void setEnvInvalidLineEnabled(const QColor &color);
    void setEnvInvalidLineDisabled(const QColor &color);
    void setEnvPointCore(const QColor &color);
    void setEnvPointRing(const QColor &color);

    void setNoteLyric(const QColor &color);
    void setNoteRestFill(const QColor &color);
    void setNoteRestLine(const QColor &color);
    void setNoteListedFill(const QColor &color);
    void setNoteListedLine(const QColor &color);
    void setNoteUnlistedFill(const QColor &color);
    void setNoteUnlistedLine(const QColor &color);
    void setNoteSelect(const QColor &color);
    void setNoteLyricBlock(const QColor &color);
    void setNoteParams(const QColor &color);
    void setNoteHighlight(const QColor &color);

    void setRubberFrame(const QColor &color);
    void setRubberFill(const QColor &color);

private:
    struct Editor {
        QColor quarterLine;
        QColor timeLine;
        QColor sectionLine;
        QColor pitchLine;
        QColor levelLine;
        QColor backDark;
        QColor backLight;
        QColor playHead;
    };

    struct Mode1 {
        QColor solidLineEnabled;
        QColor solidLineDisabled;

        QColor dashLineEnabled;
        QColor dashLineDisabled;
    };

    struct Mode2 {
        QColor solidLineEnabled;
        QColor solidLineDisabled;
        QColor dashLineEnabled;
        QColor dashLineDisabled;
        QColor invalidLineEnabled;
        QColor invalidLineDisabled;

        QColor pointCore;
        QColor pointRing;
    };

    struct Vibrato {
        QColor curvesEnabled;
        QColor curvesDisabled;
        QColor editorLines;

        QColor planeHandleBorder;
        QColor planeHandleFill;
        QColor planeHandleText;
    };

    struct Envelope {
        QColor solidLineEnabled;
        QColor solidLineDisabled;

        QColor dashLineEnabled;
        QColor dashLineDisabled;

        QColor invalidLineEnabled;
        QColor invalidLineDisabled;

        QColor pointCore;
        QColor pointRing;
    };

    struct Note {
        QColor lyric;
        QColor restFill;
        QColor restLine;
        QColor listedFill;
        QColor listedLine;
        QColor unlistedFill;
        QColor unlistedLine;
        QColor select;
        QColor lyricBlock;
        QColor params;
        QColor highlight;
    };

    struct RubberBand {
        QColor frame;
        QColor fill;
    };

    Editor editor;
    Mode1 mode1;
    Mode2 mode2;
    Vibrato vbr;
    Envelope env;
    Note note;
    RubberBand rubber;

signals:
    void themeUpdated();
    void editorThemeUpdated();
    void pitchThemeUpdated();
    void envThemeUpdated();
    void vbrHandleThemeUpdated();
    void noteThemeUpdated();
    void rubberThemeUpdated();

    void horizontalZoomRequested(int delta);
    void verticalZoomRequested(int delta);
};

#endif // NOTESSCROLLAREA_H
