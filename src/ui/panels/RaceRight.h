#ifndef USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_

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

        class RaceRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
            RaceRight(UserInterface::PacketHandler* handler, QWidget* parent = 0);
            virtual ~RaceRight() = default;
            virtual void ResizePanel(const QSize& newPanelSize) override final;

            private:
            void onOvertake(const Packet::Event::Overtake* packet);
            UserInterface::Widget::Standings* m_driverStandings;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_RACE_RIGHT_H_