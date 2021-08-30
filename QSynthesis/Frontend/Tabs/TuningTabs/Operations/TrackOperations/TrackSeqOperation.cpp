#include "TrackSeqOperation.h"

TrackSeqOperation::TrackSeqOperation(bool increase) {
    m_typeT = increase ? Add : Remove;
}
