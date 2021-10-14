#ifndef PIANOAREA_H
#define PIANOAREA_H

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>

#include "QUtauConstants.h"
#include "QUtauUtils.h"
#include "MoreWidget.h"

class EditorInterface;
class TuningGroup;
class PianoKey;

class PianoArea : public MoreWidget {
    Q_OBJECT
public:
    explicit PianoArea(EditorInterface *editor,QWidget *parent = nullptr);
    virtual ~PianoArea();

    TuningGroup *ptrs() const;

public:
    void adjustHeight();

private:
    QList<PianoKey *> m_whites;
    QList<PianoKey *> m_blacks;
    QList<QLabel *> m_labels;

    QLabel *lbToneName;
    int curNoteNum;
    QTimer *timer;

    TuningGroup *m_ptrs;

    void handleUpdateToneLabel();

private:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // PIANOAREA_H
