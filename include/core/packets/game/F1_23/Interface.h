#ifndef PACKETS_GAME_F123_INCLUDE_Interface_H_
#define PACKETS_GAME_F123_INCLUDE_Interface_H_

#include <cstdint>
#include "data/game/F1_23/Packet.h"
#include "packets/game/Interface.h"


namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            class Interface : public Packet::Game::Interface {

                public:
                // Packet interface constructor
                Interface();

                // Destructor
                virtual ~Interface();

                // Exposes the header of the current packet
                virtual const Header* GetHeader() const;

                // Returns the length of the packet in bytes, including header
                virtual const Packet::Game::F1_23::LengthBytes GetLength() const = 0;

                protected:
                virtual bool SetHeader(const Header* header);

                // Separate function to build the packet, making the code more readable
                // To be overridden and made protected by concrete packet classes
                virtual void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) = 0;

                private:
                // Header information present in all received packets
                const Header* m_header;

            };

        }

    }

}

#endif  //  PACKETS_GAME_F123_INCLUDE_Interface_H_