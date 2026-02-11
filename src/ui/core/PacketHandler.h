#ifndef USERINTERFACE_INCLUDE_PACKET_HANDLER_H_
#define USERINTERFACE_INCLUDE_PACKET_HANDLER_H_

#include <memory>
#include <QList>
#include <QMutex>
#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>
// packet headers need to be added here for signals to work
#include "packets/event/LapFinished.h"
#include "packets/event/Interface.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/PracticeSync.h"
#include "packets/event/Overtake.h"
#include "packets/event/QualiStart.h"
#include "packets/event/QualiSync.h"
#include "packets/event/RaceStart.h"
#include "packets/event/RaceSync.h"
#include "packets/event/SectorStateChanged.h"
#include "packets/event/TimeTrialStart.h"
#include "packets/event/TyreChanged.h"



namespace UserInterface {

    class PacketHandler : public QObject {

        Q_OBJECT

        public:
        PacketHandler();
        virtual ~PacketHandler();
        void AcceptPacket(QSharedPointer<Packet::Event::Interface> packet);

        signals:
        void PracticeStart(QSharedPointer<Packet::Event::PracticeStart>);
        void QualiStart(QSharedPointer<Packet::Event::QualiStart>);
        void RaceStart(QSharedPointer<Packet::Event::RaceStart>);
        void TimeTrialStart(QSharedPointer<Packet::Event::TimeTrialStart>);
        void PracticeSync(QSharedPointer<Packet::Event::PracticeSync>);
        void QualiSync(QSharedPointer<Packet::Event::QualiSync>);
        void RaceSync(QSharedPointer<Packet::Event::RaceSync>);
        void SessionEnd();
        void OvertakePerformed(QSharedPointer<Packet::Event::Overtake>);
        void PenaltyReceived(QSharedPointer<Packet::Event::PenaltyReceived>);
        void ParticipantStatusChanged(QSharedPointer<Packet::Event::ParticipantStatusChanged>);
        void LapFinished(QSharedPointer<Packet::Event::LapFinished>);
        void TyreChanged(QSharedPointer<Packet::Event::TyreChanged>);
        void SectorStateChanged(QSharedPointer<Packet::Event::SectorStateChanged>);

        private:
        void StartTimer();
        void Exec();

        // Notify functions
        void NotifySessionStartObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifySessionSyncObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifySessionEndObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifyOvertakeObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifyPenaltyObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifyStatusChangeObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifyLapObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifyTyreObservers(QSharedPointer<Packet::Event::Interface> packet);
        void NotifySectorChangeObservers(QSharedPointer<Packet::Event::Interface> packet);

        QList<QSharedPointer<Packet::Event::Interface>> m_packetList;
        QThread m_workerThread;
        QMutex m_mutex;
        QTimer m_execTimer;

    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_