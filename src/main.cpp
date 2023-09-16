#include <iostream>

#include "general/data/GeneralEnums.h"

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;
	std::cout << "Enum test: " << Packets::PacketType::MotionPacket << std::endl;
	return 0;

}