#include <iostream>
#include "packets/F1_23/EventData.h"
#include "packets/Helper.h"

int main(int argc, char* argv[]) {

	std::cout << "RaceSim Engineer online." << std::endl;

    char headerArray[static_cast<size_t>(Packet::F1_23::LengthBytes::Event)];

    //  Packet format (2023)
    headerArray[0] = 0xE7;
    headerArray[1] = 0x07;

    //  Game year (23)
    headerArray[2] = 0x17;

    //  Game major version (5)
    headerArray[3] = 0x05;

    //  Game minor version (213)
    headerArray[4] = 0xD5;

    //  Packet version (1)
    headerArray[5] = 0x01;

    //  Packet type ID (MotionExtended/13)
    headerArray[6] = 0x0D;

    //  Session UUID (15200798066961132381)
    headerArray[7] = 0x5D;
    headerArray[8] = 0xAB;
    headerArray[9] = 0xA9;
    headerArray[10] = 0xFB;
    headerArray[11] = 0x4D;
    headerArray[12] = 0x15;
    headerArray[13] = 0xF4;
    headerArray[14] = 0xD2;

    //  Session timestamp (7293.2912f)
    headerArray[15] = 0x54;
    headerArray[16] = 0xEA;
    headerArray[17] = 0xE3;
    headerArray[18] = 0x45;

    //  Frame ID (46518325)
    headerArray[19] = 0x35;
    headerArray[20] = 0xD0;
    headerArray[21] = 0xC5;
    headerArray[22] = 0x02;

    //  Overall frame ID (501357534)
    headerArray[23] = 0xDE;
    headerArray[24] = 0x1B;
    headerArray[25] = 0xE2;
    headerArray[26] = 0x1D;

    //  Player 1 index (0)
    headerArray[27] = 0x00;

    //  Player 2 index (15)
    headerArray[28] = 0x15;

    //  Event type (Overtake)
    headerArray[29] = 0x4F;
    headerArray[30] = 0x56;
    headerArray[31] = 0x54;
    headerArray[32] = 0x4B;

    //  Overtaking car index
    headerArray[33] = 0x00;

    //  Overtaken car index
    headerArray[34] = 0x09;

    Packet::IPacket* packet;

    packet = new Packet::F1_23::EventData(headerArray, new Packet::Helper(static_cast<size_t>(Packet::F1_23::LengthBytes::Event)));

    #ifndef NDEBUG
    packet->Print();
    #endif // NDEBUG

    // Helper deletion is responsability of the created packet
    delete packet;

	return 0;

}