#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QToolButton>

#include "Methods.h"
#include "QUtils.h"

// Button of double status
class IconButton : public QLabel {
    Q_OBJECT

    Q_PROPERTY(QColor upColor READ upColor WRITE setUpColor NOTIFY colorChanged)
    Q_PROPERTY(QColor overColor READ overColor WRITE setOverColor NOTIFY colorChanged)
    Q_PROPERTY(QColor downColor READ downColor WRITE setDownColor NOTIFY colorChanged)
    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor NOTIFY colorChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    explicit IconButton(QWidget *parent = nullptr);
    explicit IconButton(QSizeF padding, QWidget *parent = nullptr);

private:
    void init();

public:
    void setPadding(QSizeF padding);
    QSizeF padding() const;

    void setIcon(const QString &path);

    friend class ToolMultiButton;

    QColor upColor() const;
    void setUpColor(const QColor &upColor);

    QColor overColor() const;
    void setOverColor(const QColor &overColor);

    QColor downColor() const;
    void setDownColor(const QColor &downColor);

    QColor iconColor() const;
    void setIconColor(const QColor &iconColor);

    double radius() const;
    void setRadius(double radius);

private:
    void reloadIcons();

    void setRollState(Qs::ButtonStatus state);

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Qs::ButtonStatus rollState;
    QSizeF m_padding;

    QString m_path;
    QPixmap m_bmp;

    QColor m_upColor;
    QColor m_overColor;
    QColor m_downColor;
    QColor m_iconColor;

    double m_radius;

signals:
    void clicked();
    void press();

    void colorChanged();
    void radiusChanged();
};

#endif // ICONBUTTON_H
