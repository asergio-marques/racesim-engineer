#ifndef NETCOM_LISTENER_INCLUDE_ISOCKET_H_
#define NETCOM_LISTENER_INCLUDE_ISOCKET_H_

#include <cstdint>
#include <functional>



namespace Listener {

    class ISocket {

        public:
        ISocket() = default;
        virtual ~ISocket() = default;
        virtual bool Init() = 0;
        virtual bool Bind(const char* ipAddress, const uint16_t port, bool rebind = false) = 0;
        virtual bool RegisterFunction(std::function<void(const char*, const uint16_t)> f) = 0;
        virtual void DeregisterFunction() = 0;
        virtual void Exec() = 0;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_ISOCKET_H_