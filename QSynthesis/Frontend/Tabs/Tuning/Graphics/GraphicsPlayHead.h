#ifndef GRAPHICSPLAYHEAD_H
#define GRAPHICSPLAYHEAD_H

#include <QGraphicsRectItem>

class GraphicsPlayHead : public QGraphicsRectItem {
public:
    explicit GraphicsPlayHead(QGraphicsItem *parent = nullptr);
    ~GraphicsPlayHead();

public:
    double left() const;
    double right() const;

    bool playing() const;
    void setPlaying(bool playing);

    bool alwaysShow() const;
    void setAlwaysShow(bool alwaysShow);

private:
    QPainterPath shape() const override;

    bool m_playing;
    bool m_alwaysShow;
};

#endif // GRAPHICSPLAYHEAD_H
