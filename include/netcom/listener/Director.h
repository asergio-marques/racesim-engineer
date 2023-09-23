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
        bool setSocket(ISocket* socket);

        private:
        void OnNewDatagramAvailable(const char* datagram, const uint16_t datagramSize);

        ISocket* m_socket;
        Listener::IGameAdapter* m_gameAdapter;
        bool m_shutdown;
    
    };

};

#endif // NETCOM_LISTENER_INCLUDE_DIRECTOR_H_