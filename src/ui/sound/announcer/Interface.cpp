#include "announcer/Interface.h"

#include <QList>
#include <QObject>
#include "packets/event/Type.h"
#include "announcement/Interface.h"




UserInterface::Announcer::Interface::Interface(QObject* parent) :
    QObject(parent),
    m_installedAnnouncements() {



}



void UserInterface::Announcer::Interface::InstallAnnouncement(UserInterface::Announcement::Interface* announcement) {

    if (announcement) {

        m_installedAnnouncements.push_back(announcement);
        announcement->setParent(this);
        announcement->Activate();

    }

}