#include "announcement/PenaltyReceived.h"

#include <cstdint>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QTextToSpeech>
#include "announcement/Interface.h"
#include "data/internal/Penalty.h"
#include "PacketHandler.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/Type.h"




UserInterface::Announcement::PenaltyReceived::PenaltyReceived(UserInterface::PacketHandler* handler, QTextToSpeech* speechEngine, QObject* parent) :
    UserInterface::Announcement::Interface(parent),
    m_speechEngine(speechEngine),
    m_handler(handler) {



}



Packet::Event::Type UserInterface::Announcement::PenaltyReceived::GetAcceptedType() const {

    return Packet::Event::Type::PenaltyReceived;

}



void UserInterface::Announcement::PenaltyReceived::Activate() {

    connect(m_handler, &UserInterface::PacketHandler::PenaltyReceived,
        this, &UserInterface::Announcement::PenaltyReceived::onEvent,
            Qt::QueuedConnection);

}



void UserInterface::Announcement::PenaltyReceived::Deactivate() {

    disconnect(m_handler, &UserInterface::PacketHandler::PenaltyReceived,
        this, &UserInterface::Announcement::PenaltyReceived::onEvent);

}



void UserInterface::Announcement::PenaltyReceived::onEvent(QSharedPointer<Packet::Event::PenaltyReceived> pen) {

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
                // TODO intentionally deactivated on grounds of being annoying, but should be user configurable
                /*if (pen->m_delta > 0) {
                    penDescription = QString("received a %1 second time penalty that can be served").arg(QString::number(pen->m_delta / 1000));
                }
                else if (pen->m_delta < 0) {
                    penDescription = QString("served a %1 second time penalty").arg(QString::number(pen->m_delta / -1000));
                }*/
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
        else if (!(pen->m_fullName.empty())) {

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