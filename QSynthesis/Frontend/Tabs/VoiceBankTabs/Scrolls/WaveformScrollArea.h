#ifndef WAVEFORMSCROLLAREA_H
#define WAVEFORMSCROLLAREA_H

#include "Common/Graphics/GraphicsLinearView.h"

class WaveformScrollArea : public GraphicsLinearView {
    Q_OBJECT

    Q_PROPERTY(
        QColor sampleOffsetLine READ sampleOffsetLine WRITE setSampleOffsetLine NOTIFY themeUpdated)
    Q_PROPERTY(QColor sampleConstantLine READ sampleConstantLine WRITE setSampleConstantLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor sampleBlankLine READ sampleBlankLine WRITE setSampleBlankLine NOTIFY themeUpdated)
    Q_PROPERTY(QColor samplePreUttrLine READ samplePreUttrLine WRITE setSamplePreUttrLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(QColor sampleOverlapLine READ sampleOverlapLine WRITE setSampleOverlapLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor sampleOffsetBack READ sampleOffsetBack WRITE setSampleOffsetBack NOTIFY themeUpdated)
    Q_PROPERTY(QColor sampleConstantBack READ sampleConstantBack WRITE setSampleConstantBack NOTIFY
                   themeUpdated)
    Q_PROPERTY(
        QColor sampleBlankBack READ sampleBlankBack WRITE setSampleBlankBack NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor sampleWaveform READ sampleWaveform WRITE setSampleWaveform NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor sampleFrqCurves READ sampleFrqCurves WRITE setSampleFrqCurves NOTIFY themeUpdated)

public:
    explicit WaveformScrollArea(QWidget *parent = nullptr);
    ~WaveformScrollArea();

    QRectF viewportRect() const;

private:
    void wheelEvent(QWheelEvent *event) override;

public:
    QColor sampleOffsetLine() const;
    QColor sampleConstantLine() const;
    QColor sampleBlankLine() const;
    QColor samplePreUttrLine() const;
    QColor sampleOverlapLine() const;
    QColor sampleOffsetBack() const;
    QColor sampleConstantBack() const;
    QColor sampleBlankBack() const;
    QColor sampleWaveform() const;
    QColor sampleFrqCurves() const;

    void setSampleOffsetLine(const QColor &color);
    void setSampleConstantLine(const QColor &color);
    void setSampleBlankLine(const QColor &color);
    void setSamplePreUttrLine(const QColor &color);
    void setSampleOverlapLine(const QColor &color);
    void setSampleOffsetBack(const QColor &color);
    void setSampleConstantBack(const QColor &color);
    void setSampleBlankBack(const QColor &color);
    void setSampleWaveform(const QColor &color);
    void setSampleFrqCurves(const QColor &color);

private:
    struct Sample {
        QColor offsetLine;
        QColor constantLine;
        QColor blankLine;
        QColor preUttrLine;
        QColor overlapLine;

        QColor offsetBack;
        QColor constantBack;
        QColor blankBack;

        QColor waveform;
        QColor frqCurves;
    };

    Sample sample;

signals:
    void themeUpdated();
    void sampleThemeUpdated();

    void horizontalZoomRequested(int delta);
};

#endif // WAVEFORMSCROLLAREA_H
