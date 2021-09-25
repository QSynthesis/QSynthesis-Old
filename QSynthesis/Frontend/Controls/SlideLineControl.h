#ifndef SLIDELINECONTROL_H
#define SLIDELINECONTROL_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "FixedLineEdit.h"
#include "QUtils.h"

class SlideLineControl : public QWidget {
    Q_OBJECT
public:
    explicit SlideLineControl(QWidget *parent = NULL);
    explicit SlideLineControl(QString text, QWidget *parent = NULL);
    explicit SlideLineControl(QString text, double value, QWidget *parent = NULL);

    void setCaption(QString caption);
    QString caption() const;

    void setBlankValue(double value);
    void setMaximum(double value);
    void setMinimum(double value);
    void setSingleStep(double value);
    void setValue(double value);
    double getValue();

    void setText(QString value);
    QString getText() const;

    FixedLineEdit *Text() const;
    QSlider *Slider() const;

    void setProportion(int a, int b);
    void setMargin(int n);

    void setSpacing(int n);

    void setUnmodified(bool value);
    bool unmodified() const;

    void setPlaceholder(QString modi, QString unmo);

private:
    double value;
    double maximum, minimum, singleStep;

    QString placeholderModified, placeholderUnmodified;

    void InitSlideControl(QString text, double value);
    void onModifyAction();

    FixedLineEdit *pText;
    QDoubleValidator *pValidator;

    QSlider *pSlider;
    QLabel *pLabel;
    QGridLayout *pLayout;

    bool m_unmodified;
    double blankValue;

    bool isTextEditing;
    bool isSliderMoving;

private:
    void handleSliderChanged(int n);
    void handleTextChanged(const QString &s);

signals:
    void valueChanged(double value);
};


#endif // SLIDELINECONTROL_H
