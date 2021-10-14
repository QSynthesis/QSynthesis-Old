#ifndef PARAMSDIALAREA_H
#define PARAMSDIALAREA_H

#include <QWidget>

#include "QUtils.h"

class ParamsInterface;
class TuningGroup;

class ParamsDialArea : public QWidget {
    Q_OBJECT

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY colorChanged)
public:
    explicit ParamsDialArea(ParamsInterface *editor,QWidget *parent);
    ~ParamsDialArea();

    void setScale(Qs::Panels::Params params);

    QColor textColor() const;
    void setTextColor(const QColor &textColor);

    TuningGroup *ptrs() const;

    const double lifterZIndex = 1;

signals:
    void colorChanged();

private:
    TuningGroup *m_ptrs;

    double highest, middle, lowest;
    QColor m_textColor;

    void paintEvent(QPaintEvent *event) override;
};

#endif // PARAMSDIALAREA_H
