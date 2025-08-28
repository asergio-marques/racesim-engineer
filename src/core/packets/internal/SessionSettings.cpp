#include "packets/internal/SessionSettings.h"

#include "data/internal/Session.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"




Packet::Internal::SessionSettings::SessionSettings(const uint64_t timestamp,
    const Session::Internal::TrackInfo track, const Session::Internal::Settings settings) :
    Packet::Internal::Interface(timestamp),
    m_track(track),
    m_settings(settings) {



}



const Packet::Internal::Type Packet::Internal::SessionSettings::packetType() const {

    return Packet::Internal::Type::SessionSettings;

}