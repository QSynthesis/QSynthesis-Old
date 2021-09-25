#ifndef OTOVISIONAREA_H
#define OTOVISIONAREA_H

#include <QDebug>
#include <QHBoxLayout>
#include <QWidget>

#include "../Scrolls/WaveformScrollArea.h"
#include "QGenonSettings.h"
#include "VoiceBankArea.h"
#include "WaveformArea.h"

class OtoOperation;

class OtoVisionArea : public VoiceBankArea {
    Q_OBJECT
public:
    explicit OtoVisionArea(VoiceBankTab *tab, QWidget *parent = nullptr);
    ~OtoVisionArea();

    void initExtern();

    void saveOperation(OtoOperation *o);

    void setSampleAndIndex(const QGenonSettings &genon, int index);
    void reset();

    void setOffsetByCursor();
    void setConstantByCursor();
    void setBlankByCursor();
    void setPreUttrByCursor();
    void setOverlapByCursor();

    bool editing() const;

private:
    WaveformArea *vision;
    WaveformScrollArea *scroll;
    QHBoxLayout *mainLayout;

    bool m_editing;

    void init();

    int minWidth() const;
    void limitWidth();

    void zoomHorizontally(int delta);
    void moveHorizontally(int delta);

    void handleEditing();
    void handleEditOver(const QGenonSettings &orgSample);

    void handleHorizontalZoom(int delta);

private:
    // Events
    void resizeEvent(QResizeEvent *event) override;

signals:
    void sampleEditing(const QGenonSettings &sample);
};

#endif // OTOVISIONAREA_H
