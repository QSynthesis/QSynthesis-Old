#include "ImageLabel.h"
#include "Templates/TemporaryMenu.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMimeDatabase>
#include <QMimeType>

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent) {
    init();
}

ImageLabel::~ImageLabel() {
}

void ImageLabel::init() {
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event) {
#if defined(Q_OS_WINDOWS)
    QString revealStr = tr("Show in Explorer(&S)");
#elif defined(Q_OS_MAC)
    QString revealStr = tr("Show in Finder(&S)");
#else
    QString revealStr = tr("Show in File Manager(&S)");
#endif

    QStringList list{revealStr, "", tr("Replace..."), tr("Remove")};
    TemporaryMenu *menu = new TemporaryMenu(list, this);

    int index = menu->start();
    menu->deleteLater();

    switch (index) {
    case 0:
        emit reveal();
        break;
    case 1:
        handleReplace();
        break;
    case 2:
        emit remove();
        break;
    default:
        break;
    }
}

void ImageLabel::handleReplace() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", imageFilterString);
    if (path.isEmpty()) {
        return;
    }

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(path);
    if (!mime.name().startsWith("image/")) {
        QMessageBox::warning(this, MainTitle, tr("This file is not a valid image file!"));
        return;
    }

    emit replace(path);
}
