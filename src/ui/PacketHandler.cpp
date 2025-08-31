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



void UserInterface::PacketHandler::AcceptPacket(Packet::Event::Interface* packet) {

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
                default:
                    // whoopsie daisy
                    break;

            }

            // TODO figure out how to clean processed packets

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


void UserInterface::PacketHandler::NotifySessionStartObservers(Packet::Event::Interface* packet) {

    // no need to check for nullptr
    if (packet) {

        switch (packet->packetType()) {

            case Packet::Event::Type::PracticeStart:
                packet->markAsProcessed();
                emit PracticeStart(dynamic_cast<const Packet::Event::PracticeStart*>(packet));
                break;

            case Packet::Event::Type::QualiStart:
                packet->markAsProcessed();
                emit QualiStart(dynamic_cast<const Packet::Event::QualiStart*>(packet));
                break;

            case Packet::Event::Type::RaceStart:
                packet->markAsProcessed();
                emit RaceStart(dynamic_cast<const Packet::Event::RaceStart*>(packet));
                break;

            case Packet::Event::Type::TimeTrialStart:
                packet->markAsProcessed();
                emit TimeTrialStart(dynamic_cast<const Packet::Event::TimeTrialStart*>(packet));
                break;

            default:
                // idk
                break;

        }

    }

}



void UserInterface::PacketHandler::NotifySessionEndObservers(Packet::Event::Interface* packet) {

    // information from packet not needed for the time being
    if (packet) {

        packet->markAsProcessed();
        emit SessionEnd(true);

    }

}



void UserInterface::PacketHandler::NotifyOvertakeObservers(Packet::Event::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit OvertakePerformed(dynamic_cast<const Packet::Event::Overtake*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyPenaltyObservers(Packet::Event::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit PenaltyReceived(dynamic_cast<const Packet::Event::PenaltyReceived*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyStatusChangeObservers(Packet::Event::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit ParticipantStatusChanged(dynamic_cast<const Packet::Event::ParticipantStatusChanged*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyLapObservers(Packet::Event::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit LapFinished(dynamic_cast<const Packet::Event::LapFinished*>(packet));

    }

}



void UserInterface::PacketHandler::NotifyTyreObservers(Packet::Event::Interface* packet) {

    if (packet) {

        packet->markAsProcessed();
        emit TyreChanged(dynamic_cast<const Packet::Event::TyreChanged*>(packet));

    }

}