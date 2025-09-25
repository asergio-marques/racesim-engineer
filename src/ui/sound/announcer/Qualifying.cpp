#include "announcer/Qualifying.h"

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




UserInterface::Announcer::Qualifying::Qualifying(QObject* parent) :
    Interface(parent) {



}



QList<Packet::Event::Type> UserInterface::Announcer::Qualifying::GetAnnouncementTypes() const {

    return { Packet::Event::Type::LapFinished };

}