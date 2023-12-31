#ifndef USERINTERFACE_SCREENS_INCLUDE_LOADING_H_
#define USERINTERFACE_SCREENS_INCLUDE_LOADING_H_

#include "screens/SinglePanelInterface.h"
#include "core/ScreenType.h"



class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    class PacketHandler;

    namespace Base {

        class TextElement;
        class ImageElement;

    }

    namespace Screen {

        class Loading : public UserInterface::Screen::SinglePanelInterface {

            Q_OBJECT

            public:
                Loading(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~Loading() = default;
                virtual const UserInterface::Screen::Type Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_LOADING_H_