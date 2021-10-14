#ifndef LINEARSCROLLAREA_H
#define LINEARSCROLLAREA_H

#include <QDebug>
#include <QEvent>
#include <QScrollArea>
#include <QScrollBar>

// Scroll area with single direction
class LinearScrollArea : public QScrollArea {
    Q_OBJECT
public:
    explicit LinearScrollArea(Qt::Orientation ori,QWidget *parent = nullptr);

    Qt::Orientation orient() const;

private:
    Qt::Orientation m_orient;

private:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LINEARSCROLLAREA_H
