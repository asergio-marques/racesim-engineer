#include <AnnouncementManager.h>

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include "packets/event/Type.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualifyingStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"
#include "sound/announcement/FinishedLap.h"
//#include "sound/announcer/FreePractice.h"
//#include "sound/announcer/Qualifying.h"
#include "sound/announcer/Race.h"
//#include "sound/announcer/TimeTrial.h"



UserInterface::AnnouncementManager::AnnouncementManager(UserInterface::PacketHandler* handler) : 
    QObject(),
    m_speechEngine(new QTextToSpeech),
    m_handler(handler),
    m_activeAnnouncer(nullptr),
    m_announcements() {

    if (m_speechEngine) {

        m_speechEngine->setParent(this);

    }

    initAnnouncements();

    if (m_handler) {
    
        connect(m_handler, &UserInterface::PacketHandler::TimeTrialStart,
            this, &UserInterface::AnnouncementManager::OnTimeTrialStart);
        connect(m_handler, &UserInterface::PacketHandler::PracticeStart,
            this, &UserInterface::AnnouncementManager::OnFreePracticeStart);
        connect(m_handler, &UserInterface::PacketHandler::QualiStart,
            this, &UserInterface::AnnouncementManager::OnQualiStart);
        connect(m_handler, &UserInterface::PacketHandler::RaceStart,
            this, &UserInterface::AnnouncementManager::OnRaceStart);
        connect(m_handler, &UserInterface::PacketHandler::SessionEnd,
            this, &UserInterface::AnnouncementManager::OnSessionEnd);

    }

}



UserInterface::AnnouncementManager::~EventAnnouncer() {



}



void UserInterface::AnnouncementManager::OnPracticeStart(QSharedPointer<Packet::Event::PracticeStart> packet) {



}



void UserInterface::AnnouncementManager::OnQualiStart(QSharedPointer<Packet::Event::QualiStart> packet) {



}



void UserInterface::AnnouncementManager::OnRaceStart(QSharedPointer<Packet::Event::RaceStart> packet) {

    m_activeAnnouncer = new UserInterface::Announcer::Race(this);
    doStartAnnouncer();

}



void UserInterface::AnnouncementManager::OnTimeTrialStart(QSharedPointer<Packet::Event::TimeTrialStart> packet) {



}



void UserInterface::AnnouncementManager::OnSessionEnd(QSharedPointer<Packet::Event::SessionEnd> packet) {)

    if (m_speechEngine) {

        m_speechEngine->stop(QTextToSpeech::BoundaryHint::Utterance);

    }

    if (m_activeAnnouncer) {

        for (const auto& type : m_activeAnnouncer->GetAnnouncementTypes()) {

            auto announcement = m_announcements.value(type, nullptr);
            if (announcement) {

                announcement->setParent(this);

            }

        }

        m_activeAnnouncer->deleteLater();
        m_activeAnnouncer = nullptr;

    }

}



void UserInterface::AnnouncementManager::initAnnouncements() {
    
    UserInterface::Announcement::FinishedLap* lapAnnounce = new UserInterface::Announcement::FinishedLap(m_speechEngine, this);
    m_announcements.insert(lapAnnounce->GetAcceptedType(), lapAnnounce);

}



void UserInterface::AnnouncementManager::doStartAnnouncer() {

    if (m_activeAnnouncer) {

        for (const auto& type : m_activeAnnouncer->GetAnnouncementTypes()) {

            auto announcement = m_announcements.value(type, nullptr);
            if (announcement) {

                m_activeAnnouncer->installAnnouncement(announcement);

            }

        }

        m_activeAnnouncer->Activate();

    }

}