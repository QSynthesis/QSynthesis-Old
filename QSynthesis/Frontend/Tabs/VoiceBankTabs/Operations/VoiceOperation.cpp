#include "VoiceOperation.h"

VoiceOperation::VoiceOperation() : m_type(Unknown) {
}

VoiceOperation::~VoiceOperation() {
}

VoiceOperation::Type VoiceOperation::type() const {
    return m_type;
}

bool VoiceOperation::differ() const {
    return false;
}

VoiceOperation *VoiceOperation::next() const {
    return m_next;
}

void VoiceOperation::setNext(VoiceOperation *next) {
    m_next = next;
}
