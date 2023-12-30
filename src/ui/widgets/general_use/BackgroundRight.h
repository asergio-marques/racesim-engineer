#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_

#include "base/ImageInterface.h"
#include "base/ID.h"



namespace UserInterface {

    namespace Widget {

        class BackgroundRight final : public UserInterface::Widget::ImageInterface {

            Q_OBJECT

            public:
            BackgroundRight(UserInterface::Widget::ID id, QWidget* parent = 0);
            virtual ~BackgroundRight() = default;

            // operations
            bool Update() override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_