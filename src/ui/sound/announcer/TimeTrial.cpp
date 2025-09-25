#include "announcer/TimeTrial.h"

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




UserInterface::Announcer::TimeTrial::TimeTrial(QObject* parent) :
    Interface(parent) {



}



QList<Packet::Event::Type> UserInterface::Announcer::TimeTrial::GetAnnouncementTypes() const {

    return { };

}