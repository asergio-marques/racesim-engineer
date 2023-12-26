#ifndef NETCOM_LISTENER_INCLUDE_DIRECTOR_H_
#define NETCOM_LISTENER_INCLUDE_DIRECTOR_H_

#include <cstdint>
#include <list>
#include "packets/Broadcaster.h"

namespace NetCom {

    namespace Adapter {

        class Interface;

    }

    namespace Listener {

        class ISocket;

        class Director : public Packet::Broadcaster {

            public:
            Director();
            ~Director();

            // Initialize the socket and start the reading thread
            void Init();

            // Inject the type of socket intended to be used, automatically tries to initialize it and bind it to the user-input port
            bool setSocket(NetCom::Listener::ISocket* socket);

            // Inject the game adapter object from above, being managed by a higher-level component
            void setGameAdapter(NetCom::Adapter::Interface* gameAdapter);

            private:
            // Function to be registered into the socket for the purpose of forwarding received datagrams to the game adapter
            void OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize);

            // Internal socket wrapper object
            NetCom::Listener::ISocket* m_socket;

            // Game-specific adapter that handles the conversion logic from datagram to full game-packet
            NetCom::Adapter::Interface* m_gameAdapter;

            // Whether the director object is shutting down
            bool m_shutdown;

            // Whether the director is able to reroute data to other components for further use
            bool m_enabled;

        };

    }

}

#endif // NETCOM_LISTENER_INCLUDE_DIRECTOR_H_