#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QToolButton>

#include "QUtils.h"

class PianoKey : public QToolButton {
    Q_OBJECT
public:
    explicit PianoKey(Qs::PianoKeyColor color,QWidget *parent = nullptr);
    ~PianoKey();

    Qs::PianoKeyColor color() const;
    void setColor(const Qs::PianoKeyColor &color);

    int posFactor() const;
    void setPosFactor(int posFactor);

    int heightFactor() const;
    void setHeightFactor(int heightFactor);

private:
    Qs::PianoKeyColor m_color;

    int m_posFactor;
    int m_heightFactor;
};

#endif // PIANOKEY_H
