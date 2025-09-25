#include "announcer/FreePractice.h"

#include <QObject>
#include "announcer/Interface.h"
#include "packets/event/Type.h"




UserInterface::Announcer::FreePractice::FreePractice(QObject* parent) :
    Interface(parent) {



}



QList<Packet::Event::Type> UserInterface::Announcer::FreePractice::GetAnnouncementTypes() const {

    return { };

}