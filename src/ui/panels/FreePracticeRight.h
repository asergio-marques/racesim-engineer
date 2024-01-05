#ifndef USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_RIGHT_H_

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

    namespace Panel {

        class FreePracticeRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                FreePracticeRight(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~FreePracticeRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_RIGHT_H_