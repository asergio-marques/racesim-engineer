#ifndef USERINTERFACE_SOUND_ANNOUNCEMENT_INTERFACE_H_
#define USERINTERFACE_SOUND_ANNOUNCEMENT_INTERFACE_H_

#include <QObject>
#include "packets/event/Type.h"




namespace UserInterface {

    namespace Announcement {

        class Interface : class QObject {

            Q_OBJECT

            public:
                Interface(QObject* parent = 0);
                virtual ~Interface() = default;
                virtual Packet::Event::Type GetAcceptedType() const = 0;
                virtual void Activate() = 0;
                virtual void Deactivate() = 0;

        };

    }

}

#endif // USERINTERFACE_SOUND_ANNOUNCEMENT_INTERFACE_H_