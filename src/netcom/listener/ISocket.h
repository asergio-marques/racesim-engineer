#ifndef NETCOM_LISTENER_INCLUDE_ISOCKET_H_
#define NETCOM_LISTENER_INCLUDE_ISOCKET_H_

#include <cstdint>
#include <functional>



namespace Listener {

    class ISocket {

        public:
        ISocket() = default;
        virtual ~ISocket() = default;

        // Function to be called after socket instantiation, performs any setup necessary prior to binding; returns true if successful
        virtual bool Init() = 0;

        // Function to perform the binding of the application socket to the local machine IP and a user-defined port, must be called after Init; returns true if successful
        virtual bool Bind(const uint16_t port, bool rebind = false) = 0;

        // Registers a single function that takes in the datagram content as a char array and the length of said array, this facilitates game-dependant processing of UDP packets; returns true if successful
        virtual bool RegisterFunction(std::function<void(const char*, const uint16_t)> f) = 0;

        // Removes the currently registered function
        virtual void DeregisterFunction() = 0;

        protected:
        // Main execution loop function to be executed in a new thread
        virtual void Exec() = 0;

    };

}

#endif // NETCOM_LISTENER_INCLUDE_ISOCKET_H_