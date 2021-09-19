#ifndef LIFTERSSCROLLAREA_H
#define LIFTERSSCROLLAREA_H

#include "Common/Graphics/GraphicsLinearView.h"
#include "AppAssistant.h"

class LiftersScrollArea : public GraphicsLinearView {
    Q_OBJECT

    Q_PROPERTY(
        QColor editorTimeLine READ editorTimeLine WRITE setEditorTimeLine NOTIFY themeUpdated)
    Q_PROPERTY(QColor editorSectionLine READ editorSectionLine WRITE setEditorSectionLine NOTIFY
                   themeUpdated)
    Q_PROPERTY(QColor editorBack READ editorBack WRITE setEditorBack NOTIFY themeUpdated)
    Q_PROPERTY(QColor lifterActive READ lifterActive WRITE setLifterActive NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor lifterInactive READ lifterInactive WRITE setLifterInactive NOTIFY themeUpdated)
    Q_PROPERTY(QColor lifterActiveH READ lifterActiveH WRITE setLifterActiveH NOTIFY themeUpdated)
    Q_PROPERTY(
        QColor lifterInactiveH READ lifterInactiveH WRITE setLifterInactiveH NOTIFY themeUpdated)

public:
    explicit LiftersScrollArea(QWidget *parent = nullptr);
    virtual ~LiftersScrollArea();

    QRectF viewportRect() const;

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

    void initLight();
    void initDark();

public:
    QColor editorTimeLine() const;
    QColor editorSectionLine() const;
    QColor editorBack() const;

    QColor lifterActive() const;
    QColor lifterInactive() const;
    QColor lifterActiveH() const;
    QColor lifterInactiveH() const;

    void setEditorTimeLine(const QColor &color);
    void setEditorSectionLine(const QColor &color);
    void setEditorBack(const QColor &color);

    void setLifterActive(const QColor &color);
    void setLifterInactive(const QColor &color);
    void setLifterActiveH(const QColor &color);
    void setLifterInactiveH(const QColor &color);

private:
    struct Editor {
        QColor timeLine;
        QColor sectionLine;
        QColor back;
    };

    struct Lifter {
        QColor active;
        QColor inactive;
        QColor activeH;
        QColor inactiveH;
    };

    Editor editor;
    Lifter lifter;

signals:
    void themeUpdated();
    void editorThemeUpdated();
    void lifterThemeUpdated();
};

#endif // LIFTERSSCROLLAREA_H
