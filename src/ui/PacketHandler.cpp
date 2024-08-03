#include "PacketHandler.h"

#include <memory>
#include <QList>
#include <QObject>
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



void UserInterface::PacketHandler::AcceptPacket(Packet::Internal::Interface* packet) {

    if (packet) {

        m_packetList.push_back(packet);

    }

}



void UserInterface::PacketHandler::StartTimer() {

    m_execTimer.start();

}



void UserInterface::PacketHandler::Exec() {

    for (auto packet : m_packetList) {

        // TODO proper packet handler, for now let's cast to our hearts' delight
        if (packet) {

            switch (packet->packetType()) {

                case Packet::Internal::Type::SessionStart:
                    NotifySessionStartObservers(packet);
                    break;
                case Packet::Internal::Type::SessionEnd:
                    NotifySessionEndObservers(packet);
                    break;
                case Packet::Internal::Type::Overtake:
                    NotifyOvertakeObservers(packet);
                    break;
                case Packet::Internal::Type::PenaltyChange:
                    NotifyPenaltyChangeObservers(packet);
                    break;
                case Packet::Internal::Type::ParticipantStatusChange:
                    NotifyStatusChangeObservers(packet);
                    break;
                case Packet::Internal::Type::FinishedLapInfo:
                    NotifyFinishedLapObservers(packet);
                    break;
                default:
                    // whoopsie daisy
                    break;

            }

        }

    }

    m_packetList.clear();

}

void UserInterface::PacketHandler::CleanupList() {
    
    auto it = m_packetList.begin();
    while (it != m_packetList.end()) {

        // take care of iterator invalidation
        if (it && *it && (*it)->isProcessed()) {

            it = m_packetList.erase(it);

        }
        else {

            ++it;

        }

    }

}


void UserInterface::PacketHandler::NotifySessionStartObservers(Packet::Internal::Interface* packet) {

    // no need to check for nullptr
    auto sessionStartPacket = dynamic_cast<Packet::Internal::SessionStart*>(packet);
    if (sessionStartPacket) {

        switch (sessionStartPacket->m_sessionType) {

            case Session::Internal::Type::TimeTrial:
                sessionStartPacket->markAsProcessed();
                emit TimeTrialStart(dynamic_cast<const Packet::Internal::TimeTrialStart*>(sessionStartPacket));
                break;

            case Session::Internal::Type::FreePractice:
                sessionStartPacket->markAsProcessed();
                emit PracticeStart(dynamic_cast<const Packet::Internal::PracticeStart*>(sessionStartPacket));
                break;

            case Session::Internal::Type::Qualifying:
                sessionStartPacket->markAsProcessed();
                emit QualiStart(dynamic_cast<const Packet::Internal::QualiStart*>(sessionStartPacket));
                break;

            case Session::Internal::Type::Race:
                sessionStartPacket->markAsProcessed();
                emit RaceStart(dynamic_cast<const Packet::Internal::RaceStart*>(sessionStartPacket));
                break;

            default:
                // idk
                break;

        }

    }

}



void UserInterface::PacketHandler::NotifySessionEndObservers(Packet::Internal::Interface* packet) {

    // information from packet not needed for the time being
    if (packet) {

        packet->markAsProcessed();
        emit SessionEnd(true);

    }

}



void UserInterface::PacketHandler::NotifyOvertakeObservers(Packet::Internal::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit OvertakePerformed(dynamic_cast<const Packet::Internal::Overtake*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyPenaltyChangeObservers(Packet::Internal::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit PenaltyAssigned(dynamic_cast<const Packet::Internal::PenaltyChange*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyStatusChangeObservers(Packet::Internal::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit DriverStatusChanged(dynamic_cast<const Packet::Internal::ParticipantStatusChange*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyFinishedLapObservers(Packet::Internal::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit NewlyCompletedLap(dynamic_cast<const Packet::Internal::FinishedLapInfo*>(packet));

    }

}