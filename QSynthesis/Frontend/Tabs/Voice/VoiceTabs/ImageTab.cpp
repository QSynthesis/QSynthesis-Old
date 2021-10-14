#include "ImageTab.h"

ImageTab::ImageTab(TabWidget *parent) : BaseTab(parent) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    scroll = new ImageScrollArea();
    lbImage = new ImageLabel(scroll);
    scroll->setWidget(lbImage);

    lbImage->installEventFilter(this);

    mainLayout->addWidget(scroll);
    setLayout(mainLayout);
}

ImageTab::~ImageTab() {
}

ImageLabel *ImageTab::content() const {
    return lbImage;
}

bool ImageTab::eventFilter(QObject *obj, QEvent *event) {
//    if (obj == lbImage && event->type() == QEvent::Resize) {
//        QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(event);
//        QSize size = resizeEvent->size();
//        if (resizeEvent->oldSize().width() != size.width()) {
//            const QPixmap &bmp = lbImage->pixmap(Qt::ReturnByValue);
//            if (!bmp.isNull()) {
//                lbImage->setFixedHeight(double(bmp.height()) / bmp.width() * size.width());
//            }
//        }
//    }
    return BaseTab::eventFilter(obj, event);
}
