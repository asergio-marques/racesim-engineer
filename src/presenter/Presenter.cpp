#include "Presenter.h"

#include <memory>
#include "packets/game/Subscriber.h"



void Presenter::Presenter::OnPacketBroadcast(Packet::Game::Interface* packet) {

    // Identify packet (type, version)
    // Convert to generic app packet
    // Do presentation modifications according to settings
    // Send to UI

}