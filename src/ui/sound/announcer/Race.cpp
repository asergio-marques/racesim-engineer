#include "announcer/Race.h"

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




QList<Packet::Event::Type> UserInterface::Announcer::Interface::GetAnnouncementTypes() const {

    return { Packet::Event::Type::LapFinished };

}