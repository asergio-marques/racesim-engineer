#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_

#include "base/ImageInterface.h"
#include "base/ID.h"



namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class BackgroundRight final : public UserInterface::Widget::ImageInterface {

            Q_OBJECT

            public:
            BackgroundRight(UserInterface::Widget::ID id, QWidget* parent = 0);
            virtual ~BackgroundRight() = default;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_