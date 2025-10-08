#include "PacketHandler.h"

#include <iostream>
#include <memory>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>



UserInterface::PacketHandler::PacketHandler() :
    QObject(),
    m_packetList(),
    m_execTimer(),
    m_workerThread() {

    moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::started,
        this, &UserInterface::PacketHandler::StartTimer);
    connect(&m_execTimer, &QTimer::timeout,
        this, &UserInterface::PacketHandler::Exec);

    m_execTimer.setInterval(5);
    m_execTimer.moveToThread(&m_workerThread);
    
    m_workerThread.start();

}



UserInterface::PacketHandler::~PacketHandler() {

    m_execTimer.stop();
    m_packetList.clear();

}



void UserInterface::PacketHandler::AcceptPacket(QSharedPointer<Packet::Event::Interface> packet) {
    
    QMutexLocker locker(&m_mutex);
    if (!packet.isNull()) {
        m_packetList.push_back(packet);

    }

}



void UserInterface::PacketHandler::StartTimer() {

    m_execTimer.start();

}



void UserInterface::PacketHandler::Exec() {

    QMutexLocker locker(&m_mutex);
    for (auto& packet : m_packetList) {

        // TODO proper packet handler, for now let's cast to our hearts' delight
        if (!packet.isNull()) {

            /*if (reinterpret_cast<quintptr>(packet.data()) > 0xFFFFFFFFFFFF) {
                std::cout << "\tCorrupted packet pointer detected!\a" << std::endl;
                continue;
            }*/
            switch (packet->packetType()) {

                case Packet::Event::Type::PracticeStart:
                case Packet::Event::Type::QualiStart:
                case Packet::Event::Type::RaceStart:
                case Packet::Event::Type::TimeTrialStart:
                    NotifySessionStartObservers(packet);
                    break;
                case Packet::Event::Type::RoundSessionEnd:
                case Packet::Event::Type::TimeTrialEnd:
                    NotifySessionEndObservers(packet);
                    break;
                case Packet::Event::Type::Overtake:
                    NotifyOvertakeObservers(packet);
                    break;
                case Packet::Event::Type::PenaltyReceived:
                    NotifyPenaltyObservers(packet);
                    break;
                case Packet::Event::Type::ParticipantStatusChanged:
                    NotifyStatusChangeObservers(packet);
                    break;
                case Packet::Event::Type::LapFinished:
                    NotifyLapObservers(packet);
                    break;
                case Packet::Event::Type::TyreChanged:
                    NotifyTyreObservers(packet);
                    break;
                case Packet::Event::Type::SectorStateChanged:
                    NotifySectorChangeObservers(packet);
                    break;
                default:
                    // whoopsie daisy
                    break;

            }

        }

    }

    m_packetList.clear();

}



void UserInterface::PacketHandler::NotifySessionStartObservers(QSharedPointer<Packet::Event::Interface> packet) {

    // no need to check for nullptr
    if (packet) {

        switch (packet->packetType()) {

            case Packet::Event::Type::PracticeStart:
                emit PracticeStart(qSharedPointerDynamicCast<Packet::Event::PracticeStart>(packet));
                break;

            case Packet::Event::Type::QualiStart:
                emit QualiStart(qSharedPointerDynamicCast<Packet::Event::QualiStart>(packet));
                break;

            case Packet::Event::Type::RaceStart:
                emit RaceStart(qSharedPointerDynamicCast<Packet::Event::RaceStart>(packet));
                break;

            case Packet::Event::Type::TimeTrialStart:
                emit TimeTrialStart(qSharedPointerDynamicCast<Packet::Event::TimeTrialStart>(packet));
                break;

            default:
                // idk
                break;

        }

    }

}



void UserInterface::PacketHandler::NotifySessionEndObservers(QSharedPointer<Packet::Event::Interface> packet) {

    // information from packet not needed for the time being
    if (packet) {

        emit SessionEnd();

    }

}



void UserInterface::PacketHandler::NotifyOvertakeObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit OvertakePerformed(qSharedPointerDynamicCast<Packet::Event::Overtake>(packet));

    }

}



void UserInterface::PacketHandler::NotifyPenaltyObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit PenaltyReceived(qSharedPointerDynamicCast<Packet::Event::PenaltyReceived>(packet));

    }

}



void UserInterface::PacketHandler::NotifyStatusChangeObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit ParticipantStatusChanged(qSharedPointerDynamicCast<Packet::Event::ParticipantStatusChanged>(packet));

    }

}



void UserInterface::PacketHandler::NotifyLapObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit LapFinished(qSharedPointerDynamicCast<Packet::Event::LapFinished>(packet));

    }

}



void UserInterface::PacketHandler::NotifyTyreObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit TyreChanged(qSharedPointerDynamicCast<Packet::Event::TyreChanged>(packet));

    }

}



void UserInterface::PacketHandler::NotifySectorChangeObservers(QSharedPointer<Packet::Event::Interface> packet) {

    if (packet) {

        emit SectorStateChanged(qSharedPointerDynamicCast<Packet::Event::SectorStateChanged>(packet));

    }

}