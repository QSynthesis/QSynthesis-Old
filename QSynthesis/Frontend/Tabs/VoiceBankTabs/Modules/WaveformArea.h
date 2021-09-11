#ifndef WAVEFORMAREA_H
#define WAVEFORMAREA_H

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

#include "../Graphics/GraphicsOtoHandle.h"
#include "Graphics/GraphicsArea.h"
#include "Import/QFrequencyFile.h"
#include "Import/QWaveInfo.h"
#include "QGenonSettings.h"

class WaveformScrollArea;

class WaveformArea : public GraphicsArea {
    Q_OBJECT
public:
    explicit WaveformArea(WaveformScrollArea *parent = nullptr);
    ~WaveformArea();

    const double regionZIndex = 1;
    const double handleZIndex = 2;

public:
    void reset();
    double duration() const;

    void setWidth(int width);
    // void setWidth(int width = 0);

    QColor offsetColor() const;
    void setOffsetColor(const QColor &offsetColor);

    QColor constantColor() const;
    void setConstantColor(const QColor &constantColor);

    QColor blankColor() const;
    void setBlankColor(const QColor &blankColor);

    QColor preUttrColor() const;
    void setPreUttrColor(const QColor &preUttrColor);

    QColor overlapColor() const;
    void setOverlapColor(const QColor &overlapColor);

    QColor offsetBackColor() const;
    void setOffsetBackColor(const QColor &offsetBackColor);

    QColor constantBackColor() const;
    void setConstantBackColor(const QColor &constantBackColor);

    QColor blankBackColor() const;
    void setBlankBackColor(const QColor &blankBackColor);

    QColor waveformColor() const;
    void setWaveformColor(const QColor &waveformColor);

    QColor frqCurvesColor() const;
    void setFrqCurvesColor(const QColor &frqCurvesColor);

    int index() const;
    void setIndex(int index);

    void setSample(const QGenonSettings &genon);
    QGenonSettings sample() const;

    void setOffsetByCursor();
    void setConstantByCursor();
    void setBlankByCursor();
    void setPreUttrByCursor();
    void setOverlapByCursor();

    QPointF cursorPos() const;
    bool containsCursor() const;

    QWaveInfo waveInfo() const;

private:
    WaveformScrollArea *m_view;

    QWaveInfo m_wavefile;
    QFrequencyFile m_frqfile;

    QGenonSettings m_orgSample, m_sample;
    int m_index;

    GraphicsOtoHandle *btnOffset, *btnConstant, *btnBlank, *btnPreUttr, *btnOverlap;
    QGraphicsRectItem *wavesRect, *offsetRect, *constantRect, *blankRect;

    QColor m_offsetColor, m_constantColor, m_blankColor, m_preUttrColor, m_overlapColor;
    QColor m_offsetBackColor, m_constantBackColor, m_blankBackColor;
    QColor m_waveformColor,m_frqCurvesColor;

    void updateHandles();
    void updateRegionBack();

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void drawSingleChannel(QPainter &painter, int W, int H);
    void drawDoubleChannel(QPainter &painter, int W, int H);
    void drawFrequencyCurves(QPainter &painter, int W, int H);

    void handleOffsetMove(QPointF newPos, QPointF orgPos);
    void handleOffsetMoveNoLink(QPointF newPos, QPointF orgPos);

    void handleConstantMove(QPointF newPos, QPointF orgPos);
    void handleBlankMove(QPointF newPos, QPointF orgPos);
    void handlePreUttrMove(QPointF newPos, QPointF orgPos);
    void handleOverlapMove(QPointF newPos, QPointF orgPos);

    void handleOffsetClicked();
    void handleConstantClicked();
    void handleBlankClicked();
    void handlePreUttrClicked();
    void handleOverlapClicked();

private:
    double getOffset(double org) const;
    double getPreUttrance(double org, double offset) const;
    double getVoiceOverlap(double org, double offset) const;
    double getConstant(double org, double offset) const;
    double getBlank(double org, double offset) const;

private:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void handleSceneRectChanged(const QRectF &rect);

signals:
    void editing();
    void editOver(const QGenonSettings &orgSample);
};

#endif // WAVEFORMAREA_H
