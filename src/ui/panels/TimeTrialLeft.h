#ifndef USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_

#include <QSize>
#include "panels/Interface.h"



class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    class PacketHandler;

    namespace Widget {

        class ScreenTitle;

    }

    namespace Panel {

        class TimeTrialLeft final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                TimeTrialLeft(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~TimeTrialLeft() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

            private:
                UserInterface::Widget::ScreenTitle* m_screenTitle;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_