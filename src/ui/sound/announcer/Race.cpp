#include "announcer/Race.h"

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




UserInterface::Announcer::Race::Race(QObject* parent) :
    Interface(parent) {



}



QList<Packet::Event::Type> UserInterface::Announcer::Race::GetAnnouncementTypes() const {

    return { Packet::Event::Type::LapFinished };

}