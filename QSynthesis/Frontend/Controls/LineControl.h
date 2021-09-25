#ifndef LINECONTROL_H
#define LINECONTROL_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QWidget>

#include "FixedLineEdit.h"
#include "QUtils.h"

class LineControl : public QWidget {
    Q_OBJECT
public:
    explicit LineControl(Qt::Orientation orient, QWidget *parent = NULL);
    explicit LineControl(Qt::Orientation orient, QString text, QWidget *parent = NULL);
    explicit LineControl(Qt::Orientation orient, QString text, QString value,
                         QWidget *parent = NULL);

    void setBlankValue(double value);

    void setCaption(QString caption);

    QString caption() const {
        return pLabel->text();
    }

    void setProportion(int a, int b);
    void setMargin(int n);

    void setSpacing(int n);

    void setValue(QString value);
    QString getValue() const;

    FixedLineEdit *Text() const;

    void setUnmodified(bool value);
    bool unmodified() const;

    void setPlaceholder(QString modi, QString unmo);
    void setValidator(QValidator *v);

    Qt::Orientation orientation() const;

    void moveCursorToEnd();

private:
    QString value;

    void InitLineControl(QString text, QString value);
    void onModifyAction();
    void onTextChanged(QString s);

    FixedLineEdit *pText;
    QLabel *pLabel;
    QLayout *pLayout;
    QValidator *pValidator;

    double blankValue;
    bool m_unmodified;
    QString placeholderModified, placeholderUnmodified;

    Qt::Orientation orient;
};

#endif // LINECONTROL_H
