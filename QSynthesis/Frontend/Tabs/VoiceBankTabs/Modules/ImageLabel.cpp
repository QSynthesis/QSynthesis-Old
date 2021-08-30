#include "ImageLabel.h"

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
    m_menu = new QMenu(this);
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *event) {
#if defined(_WIN32)
    QAction *revealAction = new QAction(tr("Show in Explorer"), m_menu);
#elif defined(__APPLE__)
    QAction *revealAction = new QAction(tr("Show in Finder"), m_menu);
#else
    QAction *revealAction = new QAction(tr("Show in File manager"), m_menu);
#endif
    QAction *replaceAction = new QAction(tr("Replace..."), m_menu);
    QAction *removeAction = new QAction(tr("Remove"), m_menu);

    connect(revealAction, &QAction::triggered, this, &ImageLabel::handleRevealClicked);
    connect(replaceAction, &QAction::triggered, this, &ImageLabel::handleReplaceClicked);
    connect(removeAction, &QAction::triggered, this, &ImageLabel::handleRemoveClicked);

    m_menu->addAction(revealAction);
    m_menu->addSeparator();
    m_menu->addAction(replaceAction);
    m_menu->addAction(removeAction);

    m_menu->exec(QCursor::pos());
    m_menu->clear();
}

void ImageLabel::handleRevealClicked() {
    emit reveal();
}

void ImageLabel::handleReplaceClicked() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", imageFilterString);
    if (path.isEmpty()) {
        return;
    }

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(path);
    if (!mime.name().startsWith("image/")) {
        QMessageBox::warning(nullptr, MainTitle, tr("This file is not a valid image file!"));
        return;
    }

    emit replace(path);
}

void ImageLabel::handleRemoveClicked() {
    emit remove();
}
