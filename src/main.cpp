#include <iostream>

#include "general/data/PacketEnums.h"
#include "general/data/SessionEnums.h"
#include "netcom/packets/IPacket.h"

class ExamplePacket : public F1_23::Packet::IPacket {
    public:
    ExamplePacket() : IPacket(nullptr) {

        }
    virtual ~ExamplePacket() = default;

    const size_t PacketLength() override {
        return 0;
    }
};

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;
    F1_23::Packet::IPacket* packet = new ExamplePacket;
    if (packet) {
        std::cout << "Packet created, with length " << packet->PacketLength() << std::endl;
    }
	return 0;

}