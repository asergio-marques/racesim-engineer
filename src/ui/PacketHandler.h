#ifndef USERINTERFACE_INCLUDE_PACKET_HANDLER_H_
#define USERINTERFACE_INCLUDE_PACKET_HANDLER_H_

#include <memory>
#include <QList>
#include <QObject>
#include <QThread>
#include <QTimer>



namespace Packet {

    namespace Internal {

        class Interface;
        class PracticeStart;
        class QualiStart;
        class RaceStart;

    }
}

namespace UserInterface {

    namespace Widget {

        class Interface;

    }

    class PacketHandler : public QObject {

        Q_OBJECT

        public:
        PacketHandler();
        virtual ~PacketHandler();
        void AcceptPacket(Packet::Internal::Interface* packet);

        signals:
        void TimeTrialStart();
        void PracticeStart();
        void QualiStart();
        void RaceStart();
        void SessionEnd(bool withDelay);

        private:
        void StartTimer();
        void Exec();
        void CleanupList();

        // Notify functions
        void NotifySessionStartObservers(Packet::Internal::Interface* packet);
        void NotifySessionEndObservers(Packet::Internal::Interface* packet);

        QList<Packet::Internal::Interface*> m_packetList;
        QThread m_workerThread;
        QTimer m_execTimer;

    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_