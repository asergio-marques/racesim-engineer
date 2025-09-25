#include <AnnouncementManager.h>

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QTextToSpeech>
#include "core/PacketHandler.h"
#include "packets/event/Type.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"
#include "packets/event/RoundSessionEnd.h"
#include "sound/announcement/LapFinished.h"
#include "sound/announcement/PenaltyReceived.h"
#include "sound/announcement/TyreChanged.h"
#include "sound/announcer/FreePractice.h"
#include "sound/announcer/Qualifying.h"
#include "sound/announcer/Race.h"
#include "sound/announcer/TimeTrial.h"




UserInterface::AnnouncementManager::AnnouncementManager(UserInterface::PacketHandler* handler) : 
    QObject(),
    m_speechEngine(new QTextToSpeech),
    m_handler(handler),
    m_activeAnnouncer(nullptr),
    m_announcements() {

    if (m_speechEngine) {

        m_speechEngine->setParent(this);

        // set language to English US if available
        const QLocale locale(QLocale::English, QLocale::UnitedStates);
        if (m_speechEngine->availableLocales().contains(locale)) {

            m_speechEngine->setLocale(locale);

        }
        for (const auto& v : m_speechEngine->availableVoices()) {

            if (v.gender() == QVoice::Female &&
                v.locale() == locale) {

                m_speechEngine->setVoice(v);
                break;

            }

        }

        // set volume to 100%
        m_speechEngine->setVolume(1.0f);

        // slow down rate so it's more easily understandable
        m_speechEngine->setRate(-0.2f);

        // just a slight change, nothing too serious
        m_speechEngine->setPitch(-0.1f);

    }

    initAnnouncements();

    if (m_handler) {
    
        connect(m_handler, &UserInterface::PacketHandler::TimeTrialStart,
            this, &UserInterface::AnnouncementManager::OnTimeTrialStart);
        connect(m_handler, &UserInterface::PacketHandler::PracticeStart,
            this, &UserInterface::AnnouncementManager::OnPracticeStart);
        connect(m_handler, &UserInterface::PacketHandler::QualiStart,
            this, &UserInterface::AnnouncementManager::OnQualiStart);
        connect(m_handler, &UserInterface::PacketHandler::RaceStart,
            this, &UserInterface::AnnouncementManager::OnRaceStart);
        connect(m_handler, &UserInterface::PacketHandler::SessionEnd,
            this, &UserInterface::AnnouncementManager::OnSessionEnd);

    }

}



void UserInterface::AnnouncementManager::OnPracticeStart(QSharedPointer<Packet::Event::PracticeStart> packet) {

    m_activeAnnouncer = new UserInterface::Announcer::FreePractice(this);
    doStartAnnouncer();

}



void UserInterface::AnnouncementManager::OnQualiStart(QSharedPointer<Packet::Event::QualiStart> packet) {

    m_activeAnnouncer = new UserInterface::Announcer::Qualifying(this);
    doStartAnnouncer();

}



void UserInterface::AnnouncementManager::OnRaceStart(QSharedPointer<Packet::Event::RaceStart> packet) {

    m_activeAnnouncer = new UserInterface::Announcer::Race(this);
    doStartAnnouncer();

}



void UserInterface::AnnouncementManager::OnTimeTrialStart(QSharedPointer<Packet::Event::TimeTrialStart> packet) {

    m_activeAnnouncer = new UserInterface::Announcer::TimeTrial(this);
    doStartAnnouncer();

}



void UserInterface::AnnouncementManager::OnSessionEnd() {

    if (m_speechEngine) {

        m_speechEngine->stop(QTextToSpeech::BoundaryHint::Utterance);
        m_speechEngine->setParent(this);

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
    
    UserInterface::Announcement::LapFinished* lapAnnounce = new UserInterface::Announcement::LapFinished(m_handler, m_speechEngine, this);
    m_announcements.insert(lapAnnounce->GetAcceptedType(), lapAnnounce);

    UserInterface::Announcement::PenaltyReceived* penAnnounce = new UserInterface::Announcement::PenaltyReceived(m_handler, m_speechEngine, this);
    m_announcements.insert(penAnnounce->GetAcceptedType(), penAnnounce);

    UserInterface::Announcement::TyreChanged* tyreAnnounce = new UserInterface::Announcement::TyreChanged(m_handler, m_speechEngine, this);
    m_announcements.insert(tyreAnnounce->GetAcceptedType(), tyreAnnounce);

}



void UserInterface::AnnouncementManager::doStartAnnouncer() {

    if (m_activeAnnouncer) {

        for (const auto& type : m_activeAnnouncer->GetAnnouncementTypes()) {

            auto announcement = m_announcements.value(type, nullptr);
            if (announcement) {

                m_activeAnnouncer->InstallAnnouncement(announcement);

            }

        }

    }

}