#ifndef GENERAL_PACKETS_INCLUDE_IPACKET_H_
#define GENERAL_PACKETS_INCLUDE_IPACKET_H_

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

#endif  //  GENERAL_PACKETS_INCLUDE_IPACKET_H_