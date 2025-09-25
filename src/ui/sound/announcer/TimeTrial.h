#ifndef USERINTERFACE_SOUND_ANNOUNCER_TIME_TRIAL_H_
#define USERINTERFACE_SOUND_ANNOUNCER_TIME_TRIAL_H_

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcer {

        class TimeTrial final : public Interface {

            Q_OBJECT

            public:
            TimeTrial(QObject* parent = 0);
            virtual ~TimeTrial() = default;
            QList<Packet::Event::Type> GetAnnouncementTypes() const override final;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCER_TIME_TRIAL_H_