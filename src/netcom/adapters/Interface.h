#ifndef NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_
#define NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_

#include <vector>



namespace Packet {
    
    namespace Game {

        class Interface;

    }

    namespace Internal {

        class Interface;

    }

}

namespace NetCom {

    namespace Adapter {

        class Interface {

            public:
            Interface() = default;
            ~Interface() = default;

            // Function to be overridden by game-specific child classes that implement the conversion from byte arrays to packets of each respective game
            virtual Packet::Game::Interface* ProcessDatagram(const char* datagram) = 0;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_INTERFACE_H_