#ifndef USERINTERFACE_SOUND_ANNOUNCER_FREE_PRACTICE_H_
#define USERINTERFACE_SOUND_ANNOUNCER_FREE_PRACTICE_H_

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcer {

        class FreePractice final : public Interface {

            Q_OBJECT

            public:
            FreePractice(QObject* parent = 0);
            virtual ~FreePractice() = default;
            QList<Packet::Event::Type> GetAnnouncementTypes() const override final;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCER_FREE_PRACTICE_H_