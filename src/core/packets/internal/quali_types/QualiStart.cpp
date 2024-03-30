#include "packets/internal/quali_types/QualiStart.h"

#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"



Packet::Internal::QualiStart::QualiStart(const uint64_t timestamp, uint8_t carsClassifiedAtEnd) :
    Packet::Internal::MPSessionStart(timestamp, Session::Internal::Type::Qualifying),
    m_carsClassifiedAtEnd(carsClassifiedAtEnd) {



}