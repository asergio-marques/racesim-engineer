#ifndef USERINTERFACE_SOUND_ANNOUNCER_RACE_H_
#define USERINTERFACE_SOUND_ANNOUNCER_RACE_H_

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcer {

        class Race final : class Interface {

            Q_OBJECT

            public:
                Race(QObject* parent = 0);
                virtual ~Race() = default;
                QList<Packet::Event::Type> GetAnnouncementTypes() const override final;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCER_RACE_H_