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

        // set volume to 100%
        m_speechEngine->setVolume(1);

        // slow down rate so it's more easily understandable
        m_speechEngine->setRate(-0.2);

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

        if (!(tyre->m_fullName.empty())) {

            QString nameAnnouncement = QString("Driver %1 has pitted for %2 tyres.")
                .arg(QString::fromStdString(tyre->m_fullName))
                .arg(convertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(nameAnnouncement);

        }
        else if (tyre->m_position != UINT8_MAX) {

            QString positionAnnouncement = QString("Driver in P %1 has pitted for %2 tyres.")
                .arg(QString::number(tyre->m_position))
                .arg(convertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(positionAnnouncement);

        }
        else {

            QString unknownAnnouncement = QString("Unknown driver has pitted for %1 tyres.")
                .arg(convertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(unknownAnnouncement);

        }

    }

}



void UserInterface::EventAnnouncer::AnnouncePenaltyReceived(const Packet::Event::PenaltyReceived* pen) {

    // TODO

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