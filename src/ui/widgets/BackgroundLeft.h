#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_

#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Widget {

        class BackgroundLeft : public UserInterface::Base::ImageElement {

            public:
            BackgroundLeft(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~BackgroundLeft() = default;
            bool Update() override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_LEFT_H_