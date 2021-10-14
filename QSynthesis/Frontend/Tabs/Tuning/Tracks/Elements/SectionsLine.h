#ifndef SECTIONSLINE_H
#define SECTIONSLINE_H

#include "MoreWidget.h"

class SectionsLine : public MoreWidget {
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY colorChanged)
    Q_PROPERTY(QColor numColor READ numColor WRITE setNumColor NOTIFY colorChanged)
    Q_PROPERTY(QColor beatColor READ beatColor WRITE setBeatColor NOTIFY colorChanged)
public:
    explicit SectionsLine(QWidget *parent = nullptr);
    ~SectionsLine();

    void adjustWidth();

    int count() const;
    void setCount(int count);

    QPoint beat() const;
    void setBeat(const QPoint &beat);
    void setBeat(int num, int den);

public:
    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

    QColor numColor() const;
    void setNumColor(const QColor &numColor);

    QColor beatColor() const;
    void setBeatColor(const QColor &beatColor);

    int sectionWidth() const;
    void setSectionWidth(int width);

signals:
    void colorChanged();

private:
    QColor m_lineColor;
    QColor m_numColor;
    QColor m_beatColor;

    QPoint m_beat; // 分子

    int m_width;
    int m_count;

    void paintEvent(QPaintEvent *event) override;
};

#endif // SECTIONSLINE_H
