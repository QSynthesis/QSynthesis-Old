#ifndef OTOVARIATEOPERATION_H
#define OTOVARIATEOPERATION_H

#include "../OtoOperation.h"

class OtoVariateOperation : public OtoOperation {
public:
    OtoVariateOperation(bool increase);

    QGenonSettings sample() const;
    void setSample(const QGenonSettings &sample);

    bool differ() const;

private:
    QGenonSettings m_sample;
};

#endif // OTOVARIATEOPERATION_H
