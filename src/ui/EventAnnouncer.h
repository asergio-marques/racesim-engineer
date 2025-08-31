#ifndef USERINTERFACE_INCLUDE_EVENT_ANNOUNCER_H_
#define USERINTERFACE_INCLUDE_EVENT_ANNOUNCER_H_

#include <QObject>
#include <QTextToSpeech>
#include "data/internal/Tyre.h"
#include "packets/event/LapFinished.h"
#include "packets/event/TyreChanged.h"




class QTextToSpeech;

namespace UserInterface {

    class EventAnnouncer : public QObject {

        Q_OBJECT

        public:
        EventAnnouncer();
        virtual ~EventAnnouncer();
        void Init();
        void AnnounceFinishedLap(const Packet::Event::LapFinished* lap);
        void AnnounceTyreChanged(const Packet::Event::TyreChanged* tyre);

        private:
        QString convertVisualTyres(Tyre::Internal::Visual tyre);
        QTextToSpeech* m_speechEngine;
    };

}

#endif // USERINTERFACE_INCLUDE_PACKET_HANDLER_H_