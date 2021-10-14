#ifndef TRANSPARENTCONTAINER_H
#define TRANSPARENTCONTAINER_H

#include <QFrame>
#include <QWidget>

class TransparentContainer : public QFrame {
    Q_OBJECT

    Q_PROPERTY(QColor wallpaper READ wallpaper WRITE setWallpaper NOTIFY wallpaperChanged)
public:
    explicit TransparentContainer(QWidget *parent = nullptr);

    QColor wallpaper() const;
    void setWallpaper(const QColor &wallpaper);

private:
    QColor m_wallpaper;

    void paintEvent(QPaintEvent *event) override;

signals:
    void wallpaperChanged();
};

#endif // TRANSPARENTCONTAINER_H
