#ifndef SWITCHBUTTONUNDERLINE_H
#define SWITCHBUTTONUNDERLINE_H

#include <QPointer>
#include <QPropertyAnimation>
#include <QWidget>

class SwitchButton;
class SwitchButtonGroup;

class SwitchButtonUnderline : public QWidget {
    Q_OBJECT

    Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit SwitchButtonUnderline(QWidget *parent = nullptr);
    ~SwitchButtonUnderline();

    SwitchButtonGroup *group() const;
    void setGroup(SwitchButtonGroup *group);
    void removeGroup();

    int tweenDuration() const;
    void setTweenDuration(int duration);

    int left() const;
    void setLeft(int left);

    int right() const;
    void setRight(int right);

    QColor color() const;
    void setColor(const QColor &color);

    void setRealtimeState();

    int lineWidth() const;
    void setLineWidth(int lineWidth);

private:
    QPointer<SwitchButtonGroup> m_group;
    QPointer<SwitchButton> m_btn;

    QPropertyAnimation *m_leftAnimation;
    QPropertyAnimation *m_rightAnimation;

    int m_left;
    int m_right;
    QColor m_color;

    QPair<int, int> getTarget(SwitchButton *btn) const;
    void runAnimation();

    void setButton(SwitchButton *btn);

    void handleSwitched();

    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void leftChanged();
    void rightChanged();
    void lineWidthChanged();
    void colorChanged();
};

#endif // SWITCHBUTTONUNDERLINE_H
