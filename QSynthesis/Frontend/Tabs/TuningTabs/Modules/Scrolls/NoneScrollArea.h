#ifndef NONESCROLLAREA_H
#define NONESCROLLAREA_H

#include <QEvent>
#include <QKeyEvent>
#include <QScrollArea>
#include <QScrollBar>

// Scroll area with empty frames
class NoneScrollArea : public QWidget {
    Q_OBJECT
public:
    explicit NoneScrollArea(QWidget *parent = nullptr);
    virtual ~NoneScrollArea();

    void setWidget(QWidget *widget);
    QWidget *widget();

    void setPercentageX(double value);
    void setPercentageY(double value);
    double percentageX();
    double percentageY();

    void setValueX(int value);
    int valueX() const;

    void setValueY(int value);
    int valueY() const;

private:
    QWidget *m_widget;

    void resizeEvent(QResizeEvent *event) override;

signals:
    void resized(QResizeEvent *);
};

#endif // NONESCROLLAREA_H
