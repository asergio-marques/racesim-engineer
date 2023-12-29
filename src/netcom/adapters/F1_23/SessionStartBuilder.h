#ifndef NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_

#include <list>
#include "data/internal/Session.h"



namespace Packet {

    namespace Internal {

        class SessionStart;

    }

    namespace Game {

        namespace F1_23 {

            class ParticipantData;
            class SessionData;

        }

    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23_SessionStartBuilder {

            public:
            F1_23_SessionStartBuilder();
            virtual ~F1_23_SessionStartBuilder() = default;

            void Start();
            void CreateSessionPacket(const Packet::Game::F1_23::SessionData* gamePacket);
            void AppendParticipantData(const Packet::Game::F1_23::ParticipantData* gamePacket);
            Packet::Internal::SessionStart* Finish();

            private:
            bool m_enabled;
            bool m_waitingForParticipantData;
            bool m_waitingForSessionData;
            Packet::Internal::SessionStart* m_packetBeingBuilt;
            std::list<Session::Internal::Participant> m_listParticipants;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_SESSION_START_BUILDER_H_