#include "packets/internal/multi_use/SessionEnd.h"

#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::SessionEnd::SessionEnd(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp) {



}



const Packet::Internal::Type Packet::Internal::SessionEnd::packetType() const {

    return Packet::Internal::Type::SessionEnd;

}