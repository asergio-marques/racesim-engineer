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

}



void UserInterface::EventAnnouncer::AnnounceFinishedLap(const Packet::Event::LapFinished* lap) {

    if (m_speechEngine && lap &&
        (lap->m_infoType == Lap::Internal::InfoType::FastestLap)) {

        QString minutes = QString::number(lap->m_lapTime.m_seconds / 60);
        QString secondsPartial = QString::number(lap->m_lapTime.m_seconds % 60);
        QString hundreths = QString::number(lap->m_lapTime.m_milliseconds / 100);

        if (lap->m_isPlayer) {

            QString ownAnnouncement = QString("You have done the fastest lap with a %1 %2 point %3.")
                .arg(minutes).arg(secondsPartial).arg(hundreths);

            m_speechEngine->enqueue(ownAnnouncement);

        }


        if (!(lap->m_fullName.empty())) {

            QString nameAnnouncement = QString("Driver %1 has done the fastest lap with a %2 %3 point %4.")
                .arg(QString::fromStdString(lap->m_fullName))
                .arg(minutes).arg(secondsPartial).arg(hundreths);

            m_speechEngine->enqueue(nameAnnouncement);

        }
        else if (lap->m_currentPosition != UINT8_MAX) {

            QString positionAnnouncement = QString("Driver in P %1 has done the fastest lap with a %2 %3 point %4.")
                .arg(QString::number(lap->m_currentPosition))
                .arg(minutes).arg(secondsPartial).arg(hundreths);

            m_speechEngine->enqueue(positionAnnouncement);

        }
        else {

            QString unknownAnnouncement = QString("Unknown driver has done the fastest lap with a %1 %2 point %3.")
                .arg(minutes).arg(secondsPartial).arg(hundreths);

            m_speechEngine->enqueue(unknownAnnouncement);

        }

    }

}



void UserInterface::EventAnnouncer::AnnounceTyreChanged(const Packet::Event::TyreChanged* tyre) {

    // no need to inform if it was the player changing tyres
    if (m_speechEngine && tyre && !(tyre->m_isPlayer)) {

        if (!(tyre->m_fullName.empty())) {

            QString nameAnnouncement = QString("Driver %1 has pitted for %2 tyres.")
                .arg(QString::fromStdString(tyre->m_fullName))
                .arg(convertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(nameAnnouncement);

        }
        else if (tyre->m_currentPosition != UINT8_MAX) {

            QString positionAnnouncement = QString("Driver in P %1 has pitted for %2 tyres.")
                .arg(QString::number(tyre->m_currentPosition))
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

    if (m_speechEngine && pen) {

        QString penDescription;

        switch (pen->m_type) {

            case Penalty::Internal::Type::Warning:
                if (pen->m_delta < 1) return; // likely warnings traded for time penalty, do not announce
                else if (pen->m_delta == 1) penDescription = QString("received a warning");
                else if (pen->m_delta > 1) penDescription = QString("received %1 warnings")
                    .arg(QString::number(pen->m_delta));
                break;

            case Penalty::Internal::Type::StopGo:
                if (pen->m_delta > 0) {
                    penDescription = QString("received a %1 second time penalty that can be served").arg(QString::number(pen->m_delta / 1000));
                }
                else if (pen->m_delta < 0) {
                    penDescription = QString("served a %1 second time penalty").arg(QString::number(pen->m_delta / -1000));
                }
                break;

            case Penalty::Internal::Type::Time:
                if (pen->m_delta > 0) {
                    penDescription = QString("received a %1 second time penalty").arg(QString::number(pen->m_delta / 1000));
                }
                else if (pen->m_delta < 0) {
                    penDescription = QString("served a %1 second time penalty").arg(QString::number(pen->m_delta / -1000));
                }
                break;

            case Penalty::Internal::Type::DriveThrough:
                if (pen->m_delta < -1)  penDescription = QString("served %1 drive through penalties")
                    .arg(QString::number(pen->m_delta));
                if (pen->m_delta == -1) penDescription = QString("served a drive through penalty");
                else if (pen->m_delta == 1) penDescription = QString("received a drive through penalty");
                else if (pen->m_delta > 1) penDescription = QString("received %1 drive through penalties")
                    .arg(QString::number(pen->m_delta));
                break;

            case Penalty::Internal::Type::CurrentLapInvalid:
            case Penalty::Internal::Type::CurrentNextLapInvalid:
                // do not announce
                return;

            default:
                penDescription.append("received an unknown penalty");


        }
        if (pen->m_isPlayer) {

            QString ownAnnouncement = QString("You have %1.").arg(penDescription);
            m_speechEngine->enqueue(ownAnnouncement);

        }


        if (!(pen->m_fullName.empty())) {

            QString nameAnnouncement = QString("Driver %1 has %2.")
                .arg(QString::fromStdString(pen->m_fullName))
                .arg(penDescription);

            m_speechEngine->enqueue(nameAnnouncement);

        }
        else if (pen->m_currentPosition != UINT8_MAX) {

            QString positionAnnouncement = QString("Driver in P %1 has %2.")
                .arg(QString::number(pen->m_currentPosition))
                .arg(penDescription);

            m_speechEngine->enqueue(positionAnnouncement);

        }
        else {

            QString unknownAnnouncement = QString("Unknown driver has %1.")
                .arg(penDescription);

            m_speechEngine->enqueue(unknownAnnouncement);

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