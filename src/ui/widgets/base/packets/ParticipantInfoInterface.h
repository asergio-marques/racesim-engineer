#ifndef USERINTERFACE_WIDGET_INCLUDE_PARTICIPANT_INFO_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_PARTICIPANT_INFO_INTERFACE_H_

#include "data/internal/Session.h"



namespace UserInterface {

    namespace Widget {

        class ParticipantInfoInterface {

            public:
            virtual void Update(const Session::Internal::Participant& dataPacket, const uint8_t& initPosition) = 0;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_PARTICIPANT_INFO_INTERFACE_H_