#include "announcement/LapFinished.h"

#include <cstdint>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QTextToSpeech>
#include "announcement/Interface.h"
#include "PacketHandler.h"
#include "packets/event/LapFinished.h"
#include "packets/event/Type.h"




UserInterface::Announcement::LapFinished::LapFinished(UserInterface::PacketHandler* handler, QTextToSpeech* speechEngine, QObject* parent) :
    UserInterface::Announcement::Interface(parent),
    m_speechEngine(speechEngine),
    m_handler(handler) {



}



Packet::Event::Type UserInterface::Announcement::LapFinished::GetAcceptedType() const {

    return Packet::Event::Type::LapFinished;

}



void UserInterface::Announcement::LapFinished::Activate() {

    connect(m_handler, &UserInterface::PacketHandler::LapFinished,
        this, &UserInterface::Announcement::LapFinished::onEvent,
            Qt::QueuedConnection);

}



void UserInterface::Announcement::LapFinished::Deactivate() {

    disconnect(m_handler, &UserInterface::PacketHandler::LapFinished,
        this, &UserInterface::Announcement::LapFinished::onEvent);

}



void UserInterface::Announcement::LapFinished::onEvent(QSharedPointer<Packet::Event::LapFinished> lap) {


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
        else if (!(lap->m_fullName.empty())) {

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