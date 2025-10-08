#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_

#include "base/ImageInterface.h"
#include "base/ID.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class BackgroundFullScreen final : public UserInterface::Widget::ImageInterface {

            Q_OBJECT

            public:
            BackgroundFullScreen(UserInterface::Widget::ID id, QWidget* parent = 0);
            virtual ~BackgroundFullScreen() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_