#ifndef NOTESSCROLLAREA_H
#define NOTESSCROLLAREA_H

#include <QDebug>
#include <QGraphicsView>
#include <QMenu>

class NotesScrollArea : public QGraphicsView {
public:
    explicit NotesScrollArea(QWidget *parent = nullptr);
    virtual ~NotesScrollArea();

    QRectF viewportRect() const;

    QMenu *viewMenu;

private:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // NOTESSCROLLAREA_H
