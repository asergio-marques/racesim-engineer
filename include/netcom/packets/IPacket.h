#ifndef NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_
#define NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_

#include <cstdint>

namespace F1_23::Packet {

    class Header;
    class Helper;

    class IPacket {

        public:
            // Packet interface constructor
            IPacket(char* packetInfo);

            // Destructor
            virtual ~IPacket();

            // Exposes the header of the current packet
            virtual const Header* getHeader() const;

        private:
            // Header information present in all received packets
            Header* m_header;

    };

}

#endif  //  NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_