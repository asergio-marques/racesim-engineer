#ifndef USERINTERFACE_SOUND_ANNOUNCEMENT_LAP_FINISHED_H_
#define USERINTERFACE_SOUND_ANNOUNCEMENT_LAP_FINISHED_H_

#include <QObject>
#include <QSharedPointer>
#include "announcement/Interface.h"
#include "packets/event/LapFinished.h"
#include "packets/event/Type.h"




class QTextToSpeech;

namespace UserInterface {

    class PacketHandler;

    namespace Announcement {

        class LapFinished final : class Interface {

            Q_OBJECT

            public:
                LapFinished(UserInterface::PacketHandler handler, QTextToSpeech* speechEngine, QObject* parent = 0);
                virtual ~LapFinished() = default;
                Packet::Event::Type GetAcceptedType() const override final;
                void Activate() override final;
                void Deactivate() override final;
            
            private:
                void onEvent(QSharedPointer<Packet::Event::LapFinished> packet);
                UserInterface::PacketHandler* m_handler;
                QTextToSpeech* m_speechEngine;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCEMENT_LAP_FINISHED_H_