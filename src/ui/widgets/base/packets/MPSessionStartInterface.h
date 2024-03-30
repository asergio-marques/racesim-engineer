#ifndef USERINTERFACE_WIDGET_INCLUDE_MP_SESSION_START_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_MP_SESSION_START_INTERFACE_H_



namespace Packet {

    namespace Internal {

        class MPSessionStart;

    }

}

namespace UserInterface {

    namespace Widget {

        class MPSessionStartInterface {

            public:
            virtual void updateAtStart(const Packet::Internal::MPSessionStart* dataPacket) = 0;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_MP_SESSION_START_INTERFACE_H_