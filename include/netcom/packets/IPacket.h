#ifndef NETCOM_PACKETS_INCLUDE_IPACKET_H_
#define NETCOM_PACKETS_INCLUDE_IPACKET_H_

namespace Packet {

    class IPacket {

        public:
            // Packet interface constructor
            IPacket() = default;

            // Destructor
            virtual ~IPacket() = default;
            
            #ifndef NDEBUG
            virtual void Print() const = 0;
            #endif // NDEBUG

    };

}

#endif  //  NETCOM_PACKETS_INCLUDE_IPACKET_H_