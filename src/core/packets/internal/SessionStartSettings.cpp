#include "packets/internal/SessionStartSettings.h"

#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



Packet::Internal::SessionStartSettings::Data::Data() {

}



Packet::Internal::SessionStartSettings::SessionStartSettings(const uint64_t timestamp) :
    Packet::Internal::Interface(timestamp) {



}



const Packet::Internal::Type Packet::Internal::SessionStartSettings::packetType() const {

    return Packet::Internal::Type::SessionStartSettings;

}