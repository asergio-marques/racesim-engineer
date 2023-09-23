#ifndef NETCOM_LISTENER_INCLUDE_ISOCKET_H_
#define NETCOM_LISTENER_INCLUDE_ISOCKET_H_

#include <cstdint>



namespace Listener {

    class ISocket {

        public:
        ISocket() = default;
        virtual ~ISocket() = default;
        virtual bool Bind(const char* ip_address, const uint16_t port) = 0;
        virtual bool RegisterFunction(void (*f)(const char*, const uint16_t)) = 0;
        virtual void DeregisterFunction() = 0;
        virtual void Exec() = 0;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_ISOCKET_H_