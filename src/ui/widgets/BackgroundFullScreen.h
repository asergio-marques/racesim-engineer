#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_

#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Widget {

        class BackgroundFullScreen final : public UserInterface::Base::ImageElement {

            Q_OBJECT

            public:
            BackgroundFullScreen(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~BackgroundFullScreen() = default;

            // Operations
            bool Update() override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_FULL_SCREEN_H_