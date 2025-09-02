#ifndef GENERALIZER_ADAPTERS_INCLUDE_INTERFACE_H_
#define GENERALIZER_ADAPTERS_INCLUDE_INTERFACE_H_

#include <vector>
#include "packets/internal/Broadcaster.h"



namespace Packet {

    namespace Game {

        class Interface;

    }

    namespace Internal {

        class Interface;

    }

}

namespace Generalizer {

    namespace Adapter {

        class Interface {

            public:
            Interface() = default;
            ~Interface() = default;

            // Function to be overridden by game-specific child classes that implement the conversion from game packets to internal data packets
            virtual std::vector<Packet::Internal::Interface*> ConvertPacket(const Packet::Game::Interface* packet) = 0;

        };

    }

}

#endif // GENERALIZER_ADAPTERS_INCLUDE_INTERFACE_H_