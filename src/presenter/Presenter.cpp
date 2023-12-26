#include "Presenter.h"

#include <memory>
#include "packets/Subscriber.h"



void Presenter::Presenter::OnPacketBroadcast(const std::shared_ptr<Packet::IPacket> packet) {

    // Identify packet (type, version)
    // Convert to generic app packet
    // Do presentation modifications according to settings
    // Send to UI

}