#ifndef SLIDECONTROL_H
#define SLIDECONTROL_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "QUtils.h"
#include "FixedSpinBox.h"

class SlideControl : public QWidget {
    Q_OBJECT
public:
    explicit SlideControl(QWidget *parent = NULL);
    explicit SlideControl(QString text, QWidget *parent = NULL);
    explicit SlideControl(QString text, double value, QWidget *parent = NULL);

    void setMaximum(double value);
    void setMinimum(double value);
    void setSingleStep(double value);
    void setValue(double value);
    double getValue() const;

    QDoubleSpinBox *SpinBox() const;
    QSlider *Slider() const;

    void setCaption(QString caption);
    QString caption() const;

    void setProportion(int a, int b);
    void setMargin(int n);

    void setUnmodified(bool value);
    bool unmodified() const;

private:
    double value;
    double maximum, minimum, singleStep;

    void InitSlideControl(QString text, double value);
    void onModifyAction();

    FixedSpinBox *pSpinBox;
    QSlider *pSlider;
    QLabel *pLabel;
    QGridLayout *pLayout;

    bool m_unmodified;

public slots:
    void onSliderChanged(int n);
    void onTextChanged(double n);
};

#endif // SLIDECONTROL_H
