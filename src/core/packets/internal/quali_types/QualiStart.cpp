#include "packets/internal/quali_types/QualiStart.h"

#include "data/internal/Session.h"
#include "packets/internal/MPSessionStart.h"



Packet::Internal::QualiStart::QualiStart(uint8_t carsClassifiedAtEnd) :
    Packet::Internal::MPSessionStart(Session::Internal::Type::Qualifying),
    m_carsClassifiedAtEnd(carsClassifiedAtEnd) {



}