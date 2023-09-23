#ifndef NETCOM_PACKETS_F123_INCLUDE_IPACKET_H_
#define NETCOM_PACKETS_F123_INCLUDE_IPACKET_H_

#include <cstdint>
#include "data/F1_23/Packet.h"
#include "packets/IPacket.h"


namespace Packet {

    class Helper;

    namespace F1_23 {

        class Header;

        class IPacket : public Packet::IPacket {

            public:
            // Packet interface constructor
            IPacket(char* packetInfo);

            // Destructor
            virtual ~IPacket();

            // Exposes the header of the current packet
            virtual const Header* GetHeader() const;

            // Returns the length of the packet in bytes, including header
            virtual const Packet::F1_23::LengthBytes GetLength() const = 0;

            protected:
            // Separate function to build the packet, making the code more readable
            // To be overridden and made protected by concrete packet classes
            virtual void BuildPacket(char* packetInfo, Packet::Helper* helper) = 0;

            private:
            // Header information present in all received packets
            Header* m_header;

        };

    }

}

#endif  //  NETCOM_PACKETS_F123_INCLUDE_IPACKET_H_