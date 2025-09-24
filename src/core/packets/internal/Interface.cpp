#include "packets/internal/Interface.h"

#include <cstdint>
#include "packets/internal/Type.h"



Packet::Internal::Interface::Interface(const uint64_t timestamp) :
    m_timestamp(timestamp),
    m_processed(false) {

}



const bool Packet::Internal::Interface::isProcessed() const {

    return m_processed;

}



void Packet::Internal::Interface::markAsProcessed() {

    m_processed = true;

}