#ifndef NETCOM_LISTENER_INCLUDE_IGAMEADAPTER_H_
#define NETCOM_LISTENER_INCLUDE_IGAMEADAPTER_H_

namespace Packet {
    
    class IPacket;

}

namespace Listener {

    class IGameAdapter {

        public:
        IGameAdapter() = default;
        ~IGameAdapter() = default;

        // Function to be overridden by game-specific child classes that implement the conversion from byte arrays to packets of each respective game
        virtual Packet::IPacket* ProcessDatagram(const char* datagram) = 0;

    };

}


#endif // NETCOM_LISTENER_INCLUDE_IGAMEADAPTER_H_