#ifndef USERINTERFACE_INCLUDE_PACKET_HANDLER_H_
#define USERINTERFACE_INCLUDE_PACKET_HANDLER_H_

#include <memory>
#include <QList>
#include <QObject>
#include <QThread>
#include <QTimer>
// packet headers need to be added here for signals to work
#include "packets/internal/SessionStart.h"
#include "packets/internal/tt_types/TimeTrialStart.h"
#include "packets/internal/practice_types/PracticeStart.h"
#include "packets/internal/quali_types/QualiStart.h"
#include "packets/internal/race_types/RaceStart.h"
#include "packets/internal/race_types/Overtake.h"



namespace UserInterface {

    namespace Widget {

        class MPSessionStartInterface;

    }

    class PacketHandler : public QObject {

        Q_OBJECT

        public:
        PacketHandler();
        virtual ~PacketHandler();
        void AcceptPacket(Packet::Internal::Interface* packet);

        signals:
        void TimeTrialStart(const Packet::Internal::TimeTrialStart*);
        void PracticeStart(const Packet::Internal::PracticeStart*);
        void QualiStart(const Packet::Internal::QualiStart*);
        void RaceStart(const Packet::Internal::RaceStart*);
        void SessionEnd(bool withDelay);
        void OvertakePerformed(const Packet::Internal::Overtake*);

        private:
        void StartTimer();
        void Exec();
        void CleanupList();

        // Notify functions
        void NotifySessionStartObservers(Packet::Internal::Interface* packet);
        void NotifySessionEndObservers(Packet::Internal::Interface* packet);
        void NotifyOvertakeObservers(Packet::Internal::Interface* packet);

        QList<Packet::Internal::Interface*> m_packetList;
        QList<UserInterface::Widget::MPSessionStartInterface*> m_mpSessionStartObservers;
        QThread m_workerThread;
        QTimer m_execTimer;

    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_