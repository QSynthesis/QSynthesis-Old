#ifndef SECTIONSAREA_H
#define SECTIONSAREA_H

#include <QAction>
#include <QMenu>
#include <QWidget>

class EditorInterface;
class TuningGroup;
class GraphicsNote;

class SectionsArea : public QWidget {
    Q_OBJECT
public:
    explicit SectionsArea(EditorInterface *editor, QWidget *parent = nullptr);
    virtual ~SectionsArea();

    TuningGroup *ptrs() const;

public:
    QPoint beat() const;
    void setBeat(const QPoint &beat);
    void setBeat(int num, int den);

    void adjustWidth();

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
};

#endif // SECTIONSAREA_H
