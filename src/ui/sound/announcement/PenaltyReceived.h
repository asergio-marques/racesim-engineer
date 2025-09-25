#ifndef USERINTERFACE_SOUND_ANNOUNCEMENT_PENALTY_RECEIVED_H_
#define USERINTERFACE_SOUND_ANNOUNCEMENT_PENALTY_RECEIVED_H_

#include <QObject>
#include <QSharedPointer>
#include "announcement/Interface.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/Type.h"




class QTextToSpeech;

namespace UserInterface {

    class PacketHandler;

    namespace Announcement {

        class PenaltyReceived final : public UserInterface::Announcement::Interface {

            Q_OBJECT

            public:
                PenaltyReceived(UserInterface::PacketHandler* handler, QTextToSpeech* speechEngine, QObject* parent = 0);
                virtual ~PenaltyReceived() = default;
                Packet::Event::Type GetAcceptedType() const override final;
                void Activate() override final;
                void Deactivate() override final;
            
            private:
                void onEvent(QSharedPointer<Packet::Event::PenaltyReceived> pen);
                UserInterface::PacketHandler* m_handler;
                QTextToSpeech* m_speechEngine;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCEMENT_PENALTY_RECEIVED_H_