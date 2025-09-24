#include "PacketHandler.h"

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



void UserInterface::PacketHandler::AcceptPacket(const Packet::Event::Interface* packet) {

    if (packet) {

        // capture the packet in a shared pointer for automatic memory management
        QSharedPointer<const Packet::Event::Interface> pktPtr(packet);
        m_packetList.push_back(pktPtr);

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
                    break;
                case Packet::Event::Type::SectorStateChanged:
                    NotifySectorChangeObservers(packet);
                    break;
                default:
                    // whoopsie daisy
                    break;

            }

            // TODO figure out how to clean processed packets

        }

    }

    m_packetList.clear();

}



void UserInterface::PacketHandler::NotifySessionStartObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    // no need to check for nullptr
    if (packet) {

        switch (packet->packetType()) {

            case Packet::Event::Type::PracticeStart:
                emit PracticeStart(packet);
                break;

            case Packet::Event::Type::QualiStart:
                emit QualiStart(packet);
                break;

            case Packet::Event::Type::RaceStart:
                emit RaceStart(packet);
                break;

            case Packet::Event::Type::TimeTrialStart:
                emit TimeTrialStart(packet);
                break;

            default:
                // idk
                break;

        }

    }

}



void UserInterface::PacketHandler::NotifySessionEndObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    // information from packet not needed for the time being
    if (packet) {

        
        emit SessionEnd();

    }

}



void UserInterface::PacketHandler::NotifyOvertakeObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        emit OvertakePerformed(qSharedPointerDynamicCast<const Packet::Event::Overtake>(packet));

    }

}



void UserInterface::PacketHandler::NotifyPenaltyObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        emit PenaltyReceived(qSharedPointerDynamicCast<const Packet::Event::PenaltyReceived>(packet));

    }

}



void UserInterface::PacketHandler::NotifyStatusChangeObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        
        emit ParticipantStatusChanged(qSharedPointerDynamicCast<const Packet::Event::ParticipantStatusChanged>(packet));

    }

}



void UserInterface::PacketHandler::NotifyLapObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        
        emit LapFinished(qSharedPointerDynamicCast<const Packet::Event::LapFinished>(packet));

    }

}



void UserInterface::PacketHandler::NotifyTyreObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        
        emit TyreChanged(qSharedPointerDynamicCast<const Packet::Event::TyreChanged>(packet));

    }

}



void UserInterface::PacketHandler::NotifySectorChangeObservers(QSharedPointer<const Packet::Event::Interface> packet) {

    if (packet) {

        
        emit SectorStateChanged(qSharedPointerDynamicCast<const Packet::Event::SectorStateChanged>(packet));

    }

}