#ifndef USERINTERFACE_INCLUDE_PACKET_HANDLER_H_
#define USERINTERFACE_INCLUDE_PACKET_HANDLER_H_

#include <memory>
#include <QList>
#include <QObject>
#include <QThread>
#include <QTimer>
// packet headers need to be added here for signals to work
#include "packets/event/LapFinished.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/Overtake.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"
#include "packets/event/TyreChanged.h"



namespace UserInterface {

    namespace Widget {

        class MPSessionStartInterface;

    }

    class PacketHandler : public QObject {

        Q_OBJECT

        public:
        PacketHandler();
        virtual ~PacketHandler();
        void AcceptPacket(Packet::Event::Interface* packet);

        signals:
        void TimeTrialStart(const Packet::Event::TimeTrialStart*);
        void PracticeStart(const Packet::Event::PracticeStart*);
        void QualiStart(const Packet::Event::QualiStart*);
        void RaceStart(const Packet::Event::RaceStart*);
        void SessionEnd(bool withDelay);
        void OvertakePerformed(const Packet::Event::Overtake*);
        void PenaltyReceived(const Packet::Event::PenaltyReceived*);
        void ParticipantStatusChanged(const Packet::Event::ParticipantStatusChanged*);
        void LapFinished(const Packet::Event::LapFinished*);
        void TyreChanged(const Packet::Event::TyreChanged*);

        private:
        void StartTimer();
        void Exec();
        void CleanupList();

        // Notify functions
        void NotifySessionStartObservers(Packet::Event::Interface* packet);
        void NotifySessionEndObservers(Packet::Event::Interface* packet);
        void NotifyOvertakeObservers(Packet::Event::Interface* packet);
        void NotifyPenaltyObservers(Packet::Event::Interface* packet);
        void NotifyStatusChangeObservers(Packet::Event::Interface* packet);
        void NotifyLapObservers(Packet::Event::Interface* packet);
        void NotifyTyreObservers(Packet::Event::Interface* packet);

        QList<Packet::Event::Interface*> m_packetList;
        QList<UserInterface::Widget::MPSessionStartInterface*> m_mpSessionStartObservers;
        QThread m_workerThread;
        QTimer m_execTimer;

    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_