#include "announcement/TyreChanged.h"

#include <cstdint>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QTextToSpeech>
#include "announcement/Interface.h"
#include "data/internal/Tyre.h"
#include "PacketHandler.h"
#include "packets/event/TyreChanged.h"
#include "packets/event/Type.h"




UserInterface::Announcement::TyreChanged::TyreChanged(UserInterface::PacketHandler* handler, QTextToSpeech* speechEngine, QObject* parent) :
    UserInterface::Announcement::Interface(parent),
    m_speechEngine(speechEngine),
    m_handler(handler) {



}



Packet::Event::Type UserInterface::Announcement::TyreChanged::GetAcceptedType() const {

    return Packet::Event::Type::TyreChanged;

}



void UserInterface::Announcement::TyreChanged::Activate() {

    connect(m_handler, &UserInterface::PacketHandler::TyreChanged,
        this, &UserInterface::Announcement::TyreChanged::onEvent,
            Qt::QueuedConnection);

}



void UserInterface::Announcement::TyreChanged::Deactivate() {

    disconnect(m_handler, &UserInterface::PacketHandler::TyreChanged,
        this, &UserInterface::Announcement::TyreChanged::onEvent);

}



void UserInterface::Announcement::TyreChanged::onEvent(QSharedPointer<Packet::Event::TyreChanged> tyre) {

    // no need to inform if it was the player changing tyres
    if (m_speechEngine && tyre && !(tyre->m_isPlayer)) {

        if (!(tyre->m_fullName.empty())) {

            QString nameAnnouncement = QString("Driver %1 has pitted for %2 tyres.")
                .arg(QString::fromStdString(tyre->m_fullName))
                .arg(ConvertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(nameAnnouncement);

        }
        else if (tyre->m_currentPosition != UINT8_MAX) {

            QString positionAnnouncement = QString("Driver in P %1 has pitted for %2 tyres.")
                .arg(QString::number(tyre->m_currentPosition))
                .arg(ConvertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(positionAnnouncement);

        }
        else {

            QString unknownAnnouncement = QString("Unknown driver has pitted for %1 tyres.")
                .arg(ConvertVisualTyres(tyre->m_tyreInfo.m_visualTyre));

            m_speechEngine->enqueue(unknownAnnouncement);

        }

    }

}



QString UserInterface::Announcement::TyreChanged::ConvertVisualTyres(Tyre::Internal::Visual tyre) {

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