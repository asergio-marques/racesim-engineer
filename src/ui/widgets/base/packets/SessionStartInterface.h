#ifndef USERINTERFACE_WIDGET_INCLUDE_SESSION_START_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_SESSION_START_INTERFACE_H_



namespace Packet {

    namespace Internal {

        class SessionStart;

    }

}

namespace UserInterface {

    namespace Widget {

        class SessionStartInterface {

            public:
            virtual void Update(const Packet::Internal::SessionStart* dataPacket) = 0;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_SESSION_START_INTERFACE_H_