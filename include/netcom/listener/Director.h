#ifndef NETCOM_LISTENER_INCLUDE_DIRECTOR_H_
#define NETCOM_LISTENER_INCLUDE_DIRECTOR_H_

#include <cstdint>



namespace Listener {

    class IGameAdapter;
    class ISocket;

    class Director {
    
        public:
        Director();
        ~Director();
        
        // Inject the type of socket intended to be used, automatically tries to initialize it and bind it to the user-input port
        bool setSocket(ISocket* socket);

        private:
        // Function to be registered into the socket for the purpose of forwarding received datagrams to the game adapter
        void OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize);

        // Internal socket wrapper object
        ISocket* m_socket;

        // Game-specific adapter that handles the conversion logic from datagram to full game-packet
        Listener::IGameAdapter* m_gameAdapter;

        // Whether the director object is shutting down
        bool m_shutdown;
    
    };

};

#endif // NETCOM_LISTENER_INCLUDE_DIRECTOR_H_