#ifndef TRACKBUTTON_H
#define TRACKBUTTON_H

#include <QPushButton>

class TrackButton : public QPushButton {
    Q_OBJECT
public:
    explicit TrackButton(QWidget *parent = nullptr);
    explicit TrackButton(const QString &text, QWidget *parent = nullptr);
    ~TrackButton();

signals:
};

#endif // TRACKBUTTON_H
