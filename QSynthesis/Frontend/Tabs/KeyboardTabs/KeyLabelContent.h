#ifndef KEYLABELCONTENT_H
#define KEYLABELCONTENT_H

#include <QLabel>
#include <QWidget>

class KeyLabelContent : public QLabel {
    Q_OBJECT

    Q_PROPERTY(bool hovered READ hovered WRITE setHovered NOTIFY hoveredChanged)
private:
    bool m_hovered;

public:
    explicit KeyLabelContent(QString content, QWidget *parent = nullptr);
    explicit KeyLabelContent(QWidget *parent = nullptr);

    void setHovered(bool value);
    bool hovered() const;

private:
    void init();

signals:
    void hoveredChanged();
};

#endif // KEYLABELCONTENT_H
