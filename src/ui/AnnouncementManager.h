#ifndef USERINTERFACE_INCLUDE_ANNOUNCEMENT_MANAGER_H_
#define USERINTERFACE_INCLUDE_ANNOUNCEMENT_MANAGER_H_

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/SessionEnd.h"
#include "packets/event/TimeTrialStart.h"
#include "packets/event/Type.h"




class QTextToSpeech;

namespace UserInterface {

    class PacketHandler;

    namespace Announcer {

        class Interface;

    }

    namespace Announcement {

        class Interface;

    }

    class AnnouncementManager : public QObject {

        Q_OBJECT

        public:
        AnnouncementManager(UserInterface::PacketHandler* handler);
        virtual ~AnnouncementManager();
        void OnPracticeStart(QSharedPointer<Packet::Event::PracticeStart> packet);
        void OnQualiStart(QSharedPointer<Packet::Event::QualiStart> packet);
        void OnRaceStart(QSharedPointer<Packet::Event::RaceStart> packet);
        void OnTimeTrialStart(QSharedPointer<Packet::Event::TimeTrialStart> packet);
        void OnSessionEnd(QSharedPointer<Packet::Event::SessionEnd> packet);

        private:
        void initAnnouncements();
        void doStartAnnouncer();

        QTextToSpeech* m_speechEngine;
        UserInterface::PacketHandler* m_handler;
        UserInterface::Announcer::Interface* m_activeAnnouncer;
        QMap<Packet::Event::Type, UserInterface::Announcement::Interface*> m_announcements;
    
        };

    }

}

#endif // USERINTERFACE_INCLUDE_ANNOUNCEMENT_MANAGER_H_