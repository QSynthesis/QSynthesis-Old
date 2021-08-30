#ifndef OTOMOVEOPERATION_H
#define OTOMOVEOPERATION_H

#include "../OtoOperation.h"

class OtoMoveOperation : public OtoOperation {
public:
    OtoMoveOperation();

    int movement() const;
    void setMovement(int movement);

    QGenonSettings sample() const;
    void setSample(const QGenonSettings &sample);

    bool differ() const override;

private:
    int m_movement;
    QGenonSettings m_sample;
};

#endif // OTOMOVEOPERATION_H
