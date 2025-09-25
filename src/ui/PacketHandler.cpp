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



void UserInterface::PacketHandler::AcceptPacket(Packet::Event::Interface* packet) {

    m_mutex.lock();
    if (packet) {

        // capture the packet in a shared pointer for automatic memory management
        QSharedPointer<Packet::Event::Interface> p(packet);
        m_packetList.push_back(p);

    }
    m_mutex.unlock();

}



void UserInterface::PacketHandler::StartTimer() {

    m_execTimer.start();

}



void UserInterface::PacketHandler::Exec() {

    m_mutex.lock();
    for (auto packet : m_packetList) {

        // TODO proper packet handler, for now let's cast to our hearts' delight
        if (packet && !packet->m_isProcessed) {

            QSharedPointer<Packet::Event::Interface> pktPtr(packet);

            switch (packet->packetType()) {

                case Packet::Event::Type::PracticeStart:
                case Packet::Event::Type::QualiStart:
                case Packet::Event::Type::RaceStart:
                case Packet::Event::Type::TimeTrialStart:
                    NotifySessionStartObservers(pktPtr);
                    break;
                case Packet::Event::Type::RoundSessionEnd:
                case Packet::Event::Type::TimeTrialEnd:
                    NotifySessionEndObservers(pktPtr);
                    break;
                case Packet::Event::Type::Overtake:
                    NotifyOvertakeObservers(pktPtr);
                    break;
                case Packet::Event::Type::PenaltyReceived:
                    NotifyPenaltyObservers(pktPtr);
                    break;
                case Packet::Event::Type::ParticipantStatusChanged:
                    NotifyStatusChangeObservers(pktPtr);
                    break;
                case Packet::Event::Type::LapFinished:
                    NotifyLapObservers(pktPtr);
                    break;
                case Packet::Event::Type::TyreChanged:
                    NotifyTyreObservers(pktPtr);
                    break;
                case Packet::Event::Type::SectorStateChanged:
                    NotifySectorChangeObservers(pktPtr);
                    break;
                default:
                    // whoopsie daisy
                    break;

            }

            // TODO figure out how to clean processed packets

        }

    }

    m_packetList.clear();
    m_mutex.unlock();

}



void UserInterface::PacketHandler::NotifySessionStartObservers(QSharedPointer<Packet::Event::Interface> packet) {

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