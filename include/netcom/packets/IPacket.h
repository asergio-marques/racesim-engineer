#ifndef PACKETS_INCLUDE_IPACKET_H_
#define PACKETS_INCLUDE_IPACKET_H_

#include <cstdint>

namespace F1_23 {

    namespace Packet {

        class Header;

        class IPacket {

            public:
                // Packet interface constructor, must be passed a header always
                IPacket(Header* header);

                // Destructor
                virtual ~IPacket();

                // Length of the packet in bytes
                virtual const size_t PacketLength() = 0;

            private:
                // Header information present in all received packets
                Header* m_header;

        };

    }

}

#endif  //  PACKETS_INCLUDE_IPACKET_H_