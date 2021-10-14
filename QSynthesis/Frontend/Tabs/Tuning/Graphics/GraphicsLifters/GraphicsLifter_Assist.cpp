#include "../../Params/Areas/LiftersArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsLifter.h"

using namespace Qs::Panels;

double GraphicsLifter::convertRatioToProp(Props prop, double ratio) {
    double result = 0;
    switch (prop) {
    case Intensity:
        result = ratio * 200;
        break;
    case Modulation:
        result = (ratio - 0.5) / 0.5 * 200;
        break;
    case Velocity:
        result = (ratio >= 0.5) ? ((ratio - 0.5) / 0.5 * 100 + 100) : (ratio / 0.5 * 200 - 100);
        break;
    default:
        break;
    }
    return result;
}

double GraphicsLifter::convertPropToRatio(Props prop, double props) {
    double result = 0;
    switch (prop) {
    case Intensity:
        result = props / 200;
        break;
    case Modulation:
        result = props / 200 * 0.5 + 0.5;
        break;
    case Velocity:
        result = (props >= 100) ? ((props - 100) / 100 * 0.5 + 0.5) : ((props + 100) / 200 * 0.5);
        break;
    default:
        break;
    }
    return result;
}
