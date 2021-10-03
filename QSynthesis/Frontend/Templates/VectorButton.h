#ifndef VECTORBUTTON_H
#define VECTORBUTTON_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QToolButton>

#include "Methods.h"
#include "QUtils.h"

// Button of double status
class VectorButton : public QLabel {
    Q_OBJECT

    Q_PROPERTY(QColor upColor READ upColor WRITE setUpColor NOTIFY colorChanged)
    Q_PROPERTY(QColor overColor READ overColor WRITE setOverColor NOTIFY colorChanged)
    Q_PROPERTY(QColor downColor READ downColor WRITE setDownColor NOTIFY colorChanged)

public:
    explicit VectorButton(QWidget *parent = nullptr);
    explicit VectorButton(bool single, QSizeF padding, QWidget *parent = nullptr);

private:
    void init();

public:
    void setValues(bool single = true, QSizeF padding = QSizeF(0, 0));

    void setIcons(QString on, QString off = "");
    void setStatus(bool b);
    bool status() const;

    QColor upColor() const;
    void setUpColor(const QColor &upColor);

    QColor overColor() const;
    void setOverColor(const QColor &overColor);

    QColor downColor() const;
    void setDownColor(const QColor &downColor);

private:
    void reloadIcons();

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    bool m_status, m_single;
    Qs::ButtonStatus rollState;
    QSizeF m_padding;

    QString m_imgOn, m_imgOff;
    QPixmap bmpUp[2], bmpOver[2], bmpDown[2];

    QColor m_upColor;
    QColor m_overColor;
    QColor m_downColor;

    void setIconCore();

signals:
    void clicked();
    void press();

    void colorChanged();
};

#endif // VECTORBUTTON_H
