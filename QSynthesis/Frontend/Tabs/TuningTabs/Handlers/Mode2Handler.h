#ifndef MODE2HANDLER_H
#define MODE2HANDLER_H

#include "ScopeHandler.h"

class VibratoLineHandle;
class VibratoPlaneHandle;

class Mode2Handler : public ScopeHandler {
    Q_OBJECT
public:
    explicit Mode2Handler();
    explicit Mode2Handler(GraphicsNote *note, NotesArea *editor);
    ~Mode2Handler();

    const static QList<QControlPoint> defaultPortamento;
    const static QList<double> defaultVibrato;

    // GUI Note
    QColor m_mode1SolidLineEnabledColor;
    QColor m_mode2SolidLineEnabledColor;

    QColor m_mode1SolidLineDisabledColor;
    QColor m_mode2SolidLineDisabledColor;

    QColor m_mode1DashLineEnabledColor;
    QColor m_mode2DashLineEnabledColor;

    QColor m_mode1DashLineDisabledColor;
    QColor m_mode2DashLineDisabledColor;

    QColor m_mode2InvalidLineEnabledColor;
    QColor m_mode2InvalidLineDisabledColor;

    QColor m_vibratoButtonBorderColor;
    QColor m_vibratoButtonFillColor;
    QColor m_vibratoFrameColor;

    // GUI Point
    double m_ringWidth;
    double m_pointPadding;
    double m_pointRadius;

    QColor m_pointColor;
    QColor m_ringColor;

private:
    void init();

    /*--------------------------------------Mode2 Pitch--------------------------------------*/
    // Variate
public:
    void fromNotePoints() override; // Add Points From Mode2
    void toNotePoints() override;

    bool removePoints(const QList<GraphicsPoint *> &points) override;
    void clearPoints() override;
    void makeDefaultPoints() override;

    // States
public:
    void setSolid(bool solid) override;

    void adjustGeometry() override;
    void adjustPoints() override;

    // Assist
public:
    QRectF visionScope() const override;

    double convertPosToValueX(double x) const override;
    double convertPosToValueY(double y) const override;

    double convertValueToPosX(double x) const override;
    double convertValueToPosY(double y) const override;

    // Paint
public:
    void drawMode1(QPainter *painter);
    void drawMode2(QPainter *painter);

    void drawPoint(QPainter *painter, GraphicsPoint *p) override;

    /*--------------------------------------Mode2 Vibrato--------------------------------------*/
public:
    QList<double> Vibrato; // Vibrato Backend

    // Variate
public:
    void fromNoteVibrato();
    void toNoteVibrato();

    void replaceVibrato(const QList<double> &vbr);
    void clearVibrato();
    void makeDefaultVibrato();

    void adjustVibrato();
    void adjustVibratoLayer(QWidget *w);

    bool hasVBREditor() const;

public:
    const static double minPeriod;
    const static double maxPeriod;

    static Mode2Handler *VBREditorHolder;

    // GUI Vibrato Editor
    void initVibratoEditor();
    void removeVibrtoEditor();

    // Moving Process
    void updateVibratoLength();
    void updateVibratoGraph();
    void updateVibratoHeight();
    void updateVibratoEase();
    void updateVibratoOffset();

    // Moving Over and Save
    void saveMovingVibrato();

    // Point Reference
    QPointF pVibratoStart() const;
    QPointF pVibratoEaseInTop() const;
    QPointF pVibratoEaseInBottom() const;
    QPointF pVibratoEaseOutTop() const;
    QPointF pVibratoEaseOutBottom() const;
    QPointF pVibratoEaseInCenter() const;
    QPointF pVibratoEaseOutCenter() const;
    QPointF pVibratoEnd() const;

    QPointF pVibratoStandardStart() const;
    QPointF pVibratoStandardEnd() const;

private:
    VibratoPlaneHandle *createPlaneHandle(QString text);
    VibratoLineHandle *createLineHandle(Qt::Orientation orient);

    void removePlaneHandle(VibratoPlaneHandle *p);
    void removeLineHandle(VibratoLineHandle *p);

private:
    VibratoPlaneHandle *btnSide, *btnPhase, *btnFrequency; // Phase, Frequency Buttons
    VibratoLineHandle *btnEaseIn, *btnEaseOut, *btnTop, *btnBottom, *btnCenter;

    void updateFrequencyBySide();
    void updatePhaseByFrequency();

    void updateOthersBySide(); // Adjust all components by left border
    void updateHeightBySide();

    void updateEaseByHeight(); // Adjust ease by crests and troughs
    void updateHeightByEase(); // Adjust crests and troughs by ease

    void updateOthersByOffset();

    void restrictHeightByOffset(); // Limit crests and troughs
    void relieveHeightByOffset();  // Relase the limit temporarily

public:
    void drawVibrato(QPainter *painter);
    void drawVibratoEditor(QPainter *painter);

    /*--------------------------------------Mode1 PitchBend--------------------------------------*/
public:
    void fromNotePitches();
    void toNotePitches();
};

#endif // MODE2HANDLER_H
