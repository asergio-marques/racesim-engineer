#ifndef USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_

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

        class FreePracticeLeft final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                FreePracticeLeft(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~FreePracticeLeft() = default;
                virtual void ResizePanel(const QSize& newUsefulSize) override final;

                // Set the starting information of a new free practice session
                void Startup(QSharedPointer<Packet::Event::Interface> startInfo) override final;

                // Prepare this panel for a new session to begin, cleaning up its members
                void Cleanup() override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_