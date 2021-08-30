#ifndef ENVELOPEHANDLER_H
#define ENVELOPEHANDLER_H

#include "ScopeHandler.h"

class EnvelopeHandler : public ScopeHandler {
    Q_OBJECT
public:
    explicit EnvelopeHandler();
    explicit EnvelopeHandler(GraphicsNote *note, NotesArea *editor);
    ~EnvelopeHandler();

    const static QList<QControlPoint> defaultEnvelope;

    QList<QControlPoint> RelativePoints;

    // GUI Note
    QColor m_envSolidLineEnabledColor;
    QColor m_envSolidLineDisabledColor;

    QColor m_envDashLineEnabledColor;
    QColor m_envDashLineDisabledColor;

    QColor m_envInvalidLineEnabledColor;
    QColor m_envInvalidLineDisabledColor;

    // GUI Point
    double m_ringWidth;
    double m_pointPadding;
    double m_pointRadius;

    QColor m_pointColor;
    QColor m_ringColor;

private:
    void init();

    GraphicsPoint *createPointCore() override;

public:
    void fromNotePoints() override;
    void toNotePoints() override;

    void replacePoints(const QList<QControlPoint> &arr) override;
    bool removePoints(const QList<GraphicsPoint *> &points) override;

    void makeDefaultPoints() override;

    // States
public:
    void adjustGeometry() override;
    void adjustPoints() override;

    // Assist
public:
    QRectF visionScope() const override;

    double convertPosToValueX(double x) const override;
    double convertPosToValueY(double y) const override;

    double convertValueToPosX(double x) const override;
    double convertValueToPosY(double y) const override;

    QList<QControlPoint> fromCorrectPoints(const QList<QControlPoint> &arr);
    QList<QControlPoint> toCorrectPoints(const QList<QControlPoint> &arr);

    // Paint
public:
    void drawEnvelope(QPainter *painter);

    void drawPoint(QPainter *painter, GraphicsPoint *p) override;
};

#endif // ENVELOPEHANDLER_H
