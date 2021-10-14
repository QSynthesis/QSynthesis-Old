#ifndef PARAMSINTERFACE_H
#define PARAMSINTERFACE_H

#include <QHBoxLayout>

#include "../Base/BaseInterface.h"
#include "QUtils.h"

class ParamsForm;
class TuningGroup;
class LiftersArea;
class ParamsDialArea;
class LiftersScrollArea;

class ParamsInterface : public BaseInterface {
    Q_OBJECT
public:
    explicit ParamsInterface(ParamsForm *parent = nullptr);
    virtual ~ParamsInterface();

public:
    void setVisionStatus(Qs::Panels::Params mode);

    TuningGroup *ptrs() const;

private:
    TuningGroup *m_ptrs;

    QHBoxLayout *mainLayout;

    LiftersArea *liftersArea;
    LiftersScrollArea *liftersScroll;

    ParamsDialArea *dialArea;

private:
    void wheelEvent(QWheelEvent *event) override;

private:
    void handleHorizontalMove(int value);
};

#endif // PARAMSINTERFACE_H
