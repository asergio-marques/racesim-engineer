#ifndef NETCOM_ADAPTERS_INCLUDE_SESSION_STATE_MACHINE_H_
#define NETCOM_ADAPTERS_INCLUDE_SESSION_STATE_MACHINE_H_

#include <cstdint>



namespace NetCom {

    namespace Adapter {

        enum SessionState : uint8_t {

            Idle = 0,
            Started = 1,
            StartPacketSent = 2,

        };

        class SessionStateMachine {

            public:
            SessionStateMachine();
            ~SessionStateMachine() = default;
            const NetCom::Adapter::SessionState& GetSessionState() const;

            const bool SessionStarted();
            const bool SessionStartPacketSent();
            const bool SessionEnded();

            private:
            NetCom::Adapter::SessionState m_state;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_SESSION_STATE_MACHINE_H_