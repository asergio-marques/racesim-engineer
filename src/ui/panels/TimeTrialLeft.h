#ifndef USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_

#include <QSharedPointer>
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
                virtual void ResizePanel(const QSize& newUsefulSize) override final;

                // Set the starting information of a new time trial session
                void Startup(QSharedPointer<Packet::Event::Interface> startInfo) override final;

                // Prepare this panel for a new session to begin, cleaning up its members
                void Cleanup() override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_LEFT_H_