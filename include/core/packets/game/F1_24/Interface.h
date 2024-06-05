#ifndef PACKETS_GAME_F124_INCLUDE_INTERFACE_H_
#define PACKETS_GAME_F124_INCLUDE_INTERFACE_H_

#include <cstdint>
#include "data/game/F1_24/Packet.h"
#include "packets/game/Interface.h"


namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_24 {

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
                virtual const Packet::Game::F1_24::LengthBytes GetLength() const;

                #ifndef NDEBUG
                virtual void Print() const override;
                #endif // NDEBUG

                protected:
                virtual bool SetHeader(const Header* header);

                // Separate function to build the packet, making the code more readable
                // To be overridden and made protected by concrete packet classes
                virtual void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper);

                private:
                // Header information present in all received packets
                const Header* m_header;

            };

        }

    }

}

#endif  //  PACKETS_GAME_F124_INCLUDE_INTERFACE_H_