#include <iostream>

#include "netcom/packets/SessionData.h"
#include "netcom/packet_builders/Helper.h"

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

    size_t arrayStatus = 0;
    char testArray[20];

    // Packet format (value = 2023)
    testArray[0] = static_cast<char>(0x07);
    testArray[1] = static_cast<char>(0xE7);

    // Game year (value = 23)
    testArray[2] = static_cast<char>(23);

    // Track temperature 1 (value = -10)
    testArray[3];
    testArray[4];

    // DRS Activated (value = true)
    testArray[5] = static_cast<char>(1);

    // Track temperature 2 (value = 32)
    testArray[6];
    testArray[7];

    // Session time (value 5060203.f)
    testArray[8];
    testArray[9];
    testArray[10];
    testArray[11];

    // Total race time (value 852351123154.f)
    testArray[12];
    testArray[13];
    testArray[14];
    testArray[15];
    testArray[16];
    testArray[17];
    testArray[18];
    testArray[19];

    uint16_t output_u16     = 0;
    uint8_t output_u8       = 0;
    int16_t output_i16_1    = 0;
    bool output_b           = false;
    int16_t output_i16_2    = 0;
    float_t output_f        = 0.0f;
    double_t output_d       = 0.0f;

    std::cout << "Test of unsigned 16-bit integer variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_u16, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of unsigned 8-bit integer variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_u8, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of negative signed 16-bit integer variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_i16_1, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of boolean variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_b, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of positive signed 16-bit integer variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_i16_2, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of floating point variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_f, arrayStatus);
    std::cout << std::endl;

    std::cout << "Test of double floating point variable decoding:" << std::endl;
    F1_23::PacketBuilder::Helper::getVariable<>(testArray, output_d, arrayStatus);
    std::cout << std::endl;

	return 0;

}