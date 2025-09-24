#ifndef USERINTERFACE_INCLUDE_PACKET_HANDLER_H_
#define USERINTERFACE_INCLUDE_PACKET_HANDLER_H_

#include <memory>
#include <QList>
#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>
// packet headers need to be added here for signals to work
#include "packets/event/LapFinished.h"
#include "packets/event/Interface.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/Overtake.h"
#include "packets/event/SectorStateChanged.h"
#include "packets/event/TyreChanged.h"



namespace UserInterface {

    class PacketHandler : public QObject {

        Q_OBJECT

        public:
        PacketHandler();
        virtual ~PacketHandler();
        void AcceptPacket(const Packet::Event::Interface* packet);

        signals:
        void TimeTrialStart(QSharedPointer<const Packet::Event::Interface>);
        void PracticeStart(QSharedPointer<const Packet::Event::Interface>);
        void QualiStart(QSharedPointer<const Packet::Event::Interface>);
        void RaceStart(QSharedPointer<const Packet::Event::Interface>);
        void SessionEnd();
        void OvertakePerformed(QSharedPointer<const Packet::Event::Overtake>);
        void PenaltyReceived(QSharedPointer<const Packet::Event::PenaltyReceived>);
        void ParticipantStatusChanged(QSharedPointer<const Packet::Event::ParticipantStatusChanged>);
        void LapFinished(QSharedPointer<const Packet::Event::LapFinished>);
        void TyreChanged(QSharedPointer<const Packet::Event::TyreChanged>);
        void SectorStateChanged(QSharedPointer<const Packet::Event::SectorStateChanged>);

        private:
        void StartTimer();
        void Exec();

        // Notify functions
        void NotifySessionStartObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifySessionEndObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifyOvertakeObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifyPenaltyObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifyStatusChangeObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifyLapObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifyTyreObservers(QSharedPointer<const Packet::Event::Interface> packet);
        void NotifySectorChangeObservers(QSharedPointer<const Packet::Event::Interface> packet);

        QList<QSharedPointer<const Packet::Event::Interface>> m_packetList;
        QThread m_workerThread;
        QTimer m_execTimer;

    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_