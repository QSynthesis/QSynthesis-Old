#ifndef IMAGETAB_H
#define IMAGETAB_H

#include "Widgets/BaseTab.h"
#include "../Modules/ImageLabel.h"
#include "../Scrolls/ImageScrollArea.h"

#include <QVBoxLayout>

class ImageTab : public BaseTab {
    Q_OBJECT
public:
    explicit ImageTab(TabWidget *parent = nullptr);
    ~ImageTab();

    ImageLabel *content() const;

private:
    QVBoxLayout *mainLayout;

    ImageLabel *lbImage;
    ImageScrollArea *scroll;

    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // IMAGETAB_H
