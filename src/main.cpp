#include <iostream>

#include "netcom/packets/SessionData.h"

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;
    F1_23::Packet::IPacket* packet = new F1_23::Packet::SessionData;

    if (packet) {

        if (packet->getHeader()) {
            std::cout << "\tPacket created, has header." << std::endl;
        }
        else {
            std::cout << "\tPacket created but header is fucked." << std::endl;
        }
    }
	return 0;

}