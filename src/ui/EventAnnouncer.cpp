#include "EventAnnouncer.h"

#include <iostream>
#include <QObject>
#include <QTextToSpeech>
#include "packets/event/LapFinished.h"
#include "packets/event/TyreChanged.h"




UserInterface::EventAnnouncer::EventAnnouncer() :
    m_speechEngine(nullptr) {

}



UserInterface::EventAnnouncer::~EventAnnouncer() {



}



void UserInterface::EventAnnouncer::Init() {

    m_speechEngine = new QTextToSpeech(this);
    if (m_speechEngine) {

        // set language to English US if available
        const QLocale locale(QLocale::English, QLocale::UnitedStates);
        if (m_speechEngine->availableLocales().contains(locale)) {

            m_speechEngine->setLocale(locale);

        }
        for (const auto& v : m_speechEngine->availableVoices()) {

            if (v.gender() == QVoice::Female && v.locale() == locale) {

                m_speechEngine->setVoice(v);
                break;

            }
        }

        // set volume to 50%
        m_speechEngine->setVolume(100);

    }

}



void UserInterface::EventAnnouncer::AnnounceFinishedLap(const Packet::Event::LapFinished* lap) {

    // TODO

}



void UserInterface::EventAnnouncer::AnnounceTyreChanged(const Packet::Event::TyreChanged* tyre) {

    // no need to inform if it was the player changing tyres
    //if (m_speechEngine && tyre && !(tyre->m_isPlayer)) {
    if (m_speechEngine && tyre) {

        // TODO proper logic, like inserting in a FIFO queue to manage this overall
        if (m_speechEngine->state() == QTextToSpeech::State::Speaking) {
            m_speechEngine->stop();
        }


        QString fullAnnouncement("Driver ");

        if (!(tyre->m_fullName.empty())) {

            // if full name is available, indicate using that
            // TODO regex symbols out for whitespaces
            fullAnnouncement.append(tyre->m_fullName);

        }
        else {

            // otherwise, use the position
            fullAnnouncement.append(" in P");
            fullAnnouncement.append(QString::number(tyre->m_position));

        }

        fullAnnouncement.append(" has pitted for ");
        fullAnnouncement.append(convertVisualTyres(tyre->m_tyreInfo.m_visualTyre));
        fullAnnouncement.append(" tyres.");
        if (m_speechEngine->state() == QTextToSpeech::State::Ready) {

            m_speechEngine->say(fullAnnouncement);

        }

    }

}



QString UserInterface::EventAnnouncer::convertVisualTyres(Tyre::Internal::Visual tyre) {

    switch (tyre) {

        case Tyre::Internal::Visual::HyperSoft:
            return "Hyper Soft";

        case Tyre::Internal::Visual::SuperSoft:
            return "Super Soft";

        case Tyre::Internal::Visual::Soft:
            return "Soft";

        case Tyre::Internal::Visual::Medium:
            return "Medium";

        case Tyre::Internal::Visual::Hard:
            return "Hard";

        case Tyre::Internal::Visual::Intermediate:
            return "Intermediate";

        case Tyre::Internal::Visual::ExtremeWet:
            return "Extreme Wet";

        default:
            return "Unknown";

    }

}