#ifndef NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_
#define NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_

namespace Packet {
    
    class IPacket;

    namespace Internal {

        class Generic;

    }

}

namespace NetCom {

    namespace Adapter {

        class Interface {

            public:
            Interface() = default;
            ~Interface() = default;

            // Function to be overridden by game-specific child classes that implement the conversion from byte arrays to packets of each respective game
            virtual Packet::IPacket* ProcessDatagram(const char* datagram) = 0;

            virtual const Packet::Internal::Generic* ConvertPacket(const Packet::IPacket* packet) = 0;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_