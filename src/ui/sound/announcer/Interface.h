#ifndef USERINTERFACE_SOUND_ANNOUNCER_INTERFACE_H_
#define USERINTERFACE_SOUND_ANNOUNCER_INTERFACE_H_

#include <QList>
#include <QObject>
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcement {

        class Interface;

    }

    namespace Announcer {

        class Interface : class QObject {

            Q_OBJECT

            public:
                Interface(QObject* parent = 0);
                virtual ~Interface() = default;
                virtual QList<Packet::Event::Type> GetAnnouncementTypes() const = 0;
                void InstallAnnouncement(UserInterface::Announcement::Interface* announcement);

            protected:
                QList<UserInterface::Announcement::Interface*> m_installedAnnouncements;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCER_INTERFACE_H_