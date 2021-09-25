#ifndef SPRITEADJUSTDIALOG_H
#define SPRITEADJUSTDIALOG_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "Controls/SlideLineControl.h"
#include "Customs/TransparentContainer.h"

class SpriteAdjustDialog : public TransparentContainer {
    Q_OBJECT
public:
    explicit SpriteAdjustDialog(QWidget *parent = nullptr);
    ~SpriteAdjustDialog();

    bool visibility() const;
    int alpha() const;
    Qt::Corner corner() const;

    void setVisibility(bool visible);
    void setAlpha(int alpha);
    void setCorner(Qt::Corner corner);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *checkBoxesLayout;

    QCheckBox *cbVisible;
    SlideLineControl *scAlpha;
    QCheckBox *cbTopLeft, *cbTopRight, *cbBottomLeft, *cbBottomRight;

private:
    void handleVisibilityClicked();
    void handleCornerClicked();
    void handleAlphaChanged(double value);

signals:
    void visibilityChanged(bool visibility);
    void alphaChanged(int alpha);
    void cornerChanged(Qt::Corner corner);

    void closeRequested();
};

#endif // SPRITEADJUSTDIALOG_H
