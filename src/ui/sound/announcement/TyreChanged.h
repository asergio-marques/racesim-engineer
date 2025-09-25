#ifndef USERINTERFACE_SOUND_ANNOUNCEMENT_TYRE_CHANGED_H_
#define USERINTERFACE_SOUND_ANNOUNCEMENT_TYRE_CHANGED_H_

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "announcement/Interface.h"
#include "data/internal/Tyre.h"
#include "packets/event/TyreChanged.h"
#include "packets/event/Type.h"




class QTextToSpeech;

namespace UserInterface {

    class PacketHandler;

    namespace Announcement {

        class TyreChanged final : public UserInterface::Announcement::Interface {

            Q_OBJECT

            public:
                TyreChanged(UserInterface::PacketHandler* handler, QTextToSpeech* speechEngine, QObject* parent = 0);
                virtual ~TyreChanged() = default;
                Packet::Event::Type GetAcceptedType() const override final;
                void Activate() override final;
                void Deactivate() override final;
            
            private:
                void onEvent(QSharedPointer<Packet::Event::TyreChanged> tyre);
                QString ConvertVisualTyres(Tyre::Internal::Visual tyre);

                UserInterface::PacketHandler* m_handler;
                QTextToSpeech* m_speechEngine;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCEMENT_TYRE_CHANGED_H_