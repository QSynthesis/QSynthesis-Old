#ifndef SECTIONSAREA_H
#define SECTIONSAREA_H

#include <QAction>
#include <QMenu>

class EditorInterface;
class TuningGroup;
class GraphicsNote;

#include "MoreWidget.h"

class SectionsArea : public MoreWidget {
    Q_OBJECT

    Q_PROPERTY(
        QColor noteTempoColor READ noteTempoColor WRITE setNoteTempoColor NOTIFY colorChanged)
    Q_PROPERTY(
        QColor globalTempoColor READ globalTempoColor WRITE setGlobalTempoColor NOTIFY colorChanged)
    Q_PROPERTY(QColor beatColor READ beatColor WRITE setBeatColor NOTIFY colorChanged)
    Q_PROPERTY(QColor numColor READ numColor WRITE setNumColor NOTIFY colorChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY colorChanged)

public:
    explicit SectionsArea(EditorInterface *editor, QWidget *parent = nullptr);
    virtual ~SectionsArea();

    TuningGroup *ptrs() const;

public:
    QPoint beat() const;
    void setBeat(const QPoint &beat);
    void setBeat(int num, int den);

    void adjustWidth();

public:
    QColor noteTempoColor() const;
    void setNoteTempoColor(const QColor &noteTempoColor);

    QColor globalTempoColor() const;
    void setGlobalTempoColor(const QColor &globalTempoColor);

    QColor beatColor() const;
    void setBeatColor(const QColor &beatColor);

    QColor numColor() const;
    void setNumColor(const QColor &numColor);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

private:
    void handleModifyGlobalTempo();
    void handleModifyTempo();
    void handleRemoveTempo();

private:
    TuningGroup *m_ptrs;

    QMenu *m_menu;
    GraphicsNote *currentNote;

    QPoint m_beat; // 分子

    QColor m_lineColor;
    QColor m_numColor;
    QColor m_beatColor;

    QColor m_globalTempoColor;
    QColor m_noteTempoColor;

    void paintEvent(QPaintEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void colorChanged();
};

#endif // SECTIONSAREA_H
