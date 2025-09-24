#ifndef USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_

#include <QSharedPointer>
#include <QSize>
#include "panels/Interface.h"



class QWidget;

namespace Packet {

    namespace Event {

        class Overtake;

    }

}

namespace UserInterface {

    class PacketHandler;

    namespace Widget {

        class Standings;

    }

    namespace Panel {

        class QualifyingRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
            QualifyingRight(UserInterface::PacketHandler* handler, QWidget* parent = 0);
            virtual ~QualifyingRight() = default;
            virtual void ResizePanel(const QSize& newUsefulSize) override final;

            // Set the starting information of a new qualifying session
            void Startup(QSharedPointer<Packet::Event::Interface> startInfo) override final;

            // Prepare this panel for a new session to begin, cleaning up its members
            void Cleanup() override final;

            private:
            UserInterface::Widget::Standings* m_driverStandings;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_