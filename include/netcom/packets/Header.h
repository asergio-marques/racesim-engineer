#ifndef NETCOM_PACKETS_INCLUDE_F123_HEADER_H_
#define NETCOM_PACKETS_INCLUDE_F123_HEADER_H_

#include <cstdint>
#include <math.h>
#include "core/data/Packet.h"



namespace F1_23 {

    namespace PacketBuilder {
        
        class Header;

    }

    namespace Packet {

        class Header {

            friend F1_23::PacketBuilder::Header;

            public:
                Header();
                virtual ~Header() = default;

                // Getters for internal infos
                const Type getPacketType() const;

                #ifndef NDEBUG
                void print() const;
                #endif // NDEBUG

            private:
                //  "2023" for F1 23
                uint16_t    m_packetFormat;

                //  Game year - last two digits e.g. 23
                uint8_t     m_gameYear;

                //  Game major version - "X.00"
                uint8_t     m_gameMajorVersion;

                //  Game minor version - "1.XX"
                uint8_t     m_gameMinorVersion;

                //  Version of this packet type, all start from 1
                uint8_t     m_packetVersion;

                //  Identifier for the packet type
                Type        m_packetId;

                //  Unique identifier for the session
                uint64_t    m_sessionUID;

                //  Session timestamp
                float_t     m_sessionTime;

                //  Identifier for the frame the data was retrieved on
                uint32_t    m_frameIdentifier;

                //  Overall identifier for the frame the data was retrieved on,
                //  doesn't go back after flashbacks
                uint32_t    m_overallFrameIdentifier;

                //  Index of player 1 car in the array
                uint8_t     m_carIndexPlayer1;

                //  Index of player 2 car in the array in Split Screen mode, 
                //  255 if no second player
                uint8_t     m_carIndexPlayer2;

        };

    }

}

#endif  //  NETCOM_PACKETS_INCLUDE_F123_HEADER_H_