#include "packets/internal/Interface.h"

#include <cstdint>
#include <iostream>
#include "packets/internal/Type.h"



Packet::Internal::Interface::Interface(const uint64_t timestamp) :
    m_timestamp(timestamp),
    m_processed(false) {

}



Packet::Internal::Interface::~Interface() {

    std::cout << "Internal packet was destroyed" << std::endl;

}



const bool Packet::Internal::Interface::isProcessed() const {

    return m_processed;

}



void Packet::Internal::Interface::markAsProcessed() {

    m_processed = true;

}