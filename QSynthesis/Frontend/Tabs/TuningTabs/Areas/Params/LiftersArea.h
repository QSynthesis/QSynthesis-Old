#ifndef LIFTERSAREA_H
#define LIFTERSAREA_H

#include "QUtils.h"
#include "Utils/ItemList.h"

#include "../../Graphics/GraphicsLifter.h"
#include "Graphics/GraphicsArea.h"

class ParamsInterface;
class TuningGroup;
class LiftersScrollArea;
class GraphicsNote;

class LiftersArea : public GraphicsArea {
    Q_OBJECT
public:
    explicit LiftersArea(ParamsInterface *editor, LiftersScrollArea *parent = nullptr);
    ~LiftersArea();

    void updateColorTheme();

    TuningGroup *ptrs() const;

    LiftersScrollArea *view() const;

    ItemList<GraphicsLifter> LiftersList;

    Qs::Panels::Params prop() const;
    void setProp(const Qs::Panels::Params &prop);

    double standardHeight() const;

    const double lifterZIndex = 1;

public:
    QColor timeLineColor() const;
    void setTimeLineColor(const QColor &timeLineColor);

    QColor sectionLineColor() const;
    void setSectionLineColor(const QColor &sectionLineColor);

    QColor backColor() const;
    void setBackColor(const QColor &backColor);

public:
    bool isPlaying() const;

private:
    QColor m_timeLineColor;
    QColor m_sectionLineColor;
    QColor m_backColor;

private:
    TuningGroup *m_ptrs;

    LiftersScrollArea *m_view;

    Qs::Panels::Params m_prop;

    double m_standardHeight;

public:
    GraphicsLifter *createLifter(GraphicsNote *p);
    void removeLifter(GraphicsLifter *p);

public:
    void adjustWidth();
    void updateBackground();

public:
    void prepareMove(GraphicsLifter *p);
    void refreshMove(GraphicsLifter *p);
    void endMove(GraphicsLifter *p);

private:
    void handleSceneRectChanged(const QRectF &rect);

signals:
    void colorChanged();
};

#endif // LIFTERSAREA_H
