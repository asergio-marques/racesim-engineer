#ifndef NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_
#define NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_

#include <cstdint>
#include "data/Packet.h"

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
            
            // Returns the length of the packet in bytes, including header
            virtual const F1_23::Packet::LengthBytes getLength() const = 0;
            
            #ifndef NDEBUG
            virtual void print() const = 0;
            #endif // NDEBUG


        private:
            // Header information present in all received packets
            Header* m_header;

    };

}

#endif  //  NETCOM_PACKETS_INCLUDE_F123_IPACKET_H_