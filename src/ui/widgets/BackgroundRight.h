#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_

#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Widget {

        class BackgroundRight : public UserInterface::Base::ImageElement {

            public:
            BackgroundRight(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~BackgroundRight() = default;
            bool Update() override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_