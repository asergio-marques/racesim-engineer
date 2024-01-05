#ifndef USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_

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

        class QualifyingRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                QualifyingRight(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~QualifyingRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_QUALIFYING_RIGHT_H_