#ifndef USERINTERFACE_PANELS_INCLUDE_LOADING_H_
#define USERINTERFACE_PANELS_INCLUDE_LOADING_H_

#include "panels/Interface.h"



class QResizeEvent;
class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}



namespace UserInterface {

    class PacketHandler;

    namespace Widget {

        class LoadingIcon;
        class ScreenTitle;

    }

    namespace Panel {

        class Loading final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                Loading(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~Loading() = default;

            private:
                UserInterface::Widget::LoadingIcon* m_loadingIcon;
                UserInterface::Widget::ScreenTitle* m_loadingText;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_LOADING_H_