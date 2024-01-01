#ifndef USERINTERFACE_WIDGET_INCLUDE_SOLO_SESSION_START_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_SOLO_SESSION_START_INTERFACE_H_



namespace Packet {

    namespace Internal {

        class SoloSessionStart;

    }

}

namespace UserInterface {

    namespace Widget {

        class SoloSessionStartInterface {

            public:
            virtual void Update(const Packet::Internal::SoloSessionStart* dataPacket) = 0;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_SOLO_SESSION_START_INTERFACE_H_