#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_

#include "base/ImageInterface.h"
#include "base/ID.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class BackgroundLeft final : public UserInterface::Widget::ImageInterface {

            Q_OBJECT

            public:
            BackgroundLeft(UserInterface::Widget::ID id, QWidget* parent = 0);
            virtual ~BackgroundLeft() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_