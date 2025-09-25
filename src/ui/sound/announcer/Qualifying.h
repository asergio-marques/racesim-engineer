#ifndef USERINTERFACE_SOUND_ANNOUNCER_QUALIFYING_H_
#define USERINTERFACE_SOUND_ANNOUNCER_QUALIFYING_H_

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcer {

        class Qualifying final : public Interface {

            Q_OBJECT

            public:
            Qualifying(QObject* parent = 0);
            virtual ~Qualifying() = default;
            QList<Packet::Event::Type> GetAnnouncementTypes() const override final;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCER_QUALIFYING_H_