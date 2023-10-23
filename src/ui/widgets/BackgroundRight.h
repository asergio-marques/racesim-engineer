#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_

#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Widget {

        class BackgroundRight final : public UserInterface::Base::ImageElement {

            Q_OBJECT

            public:
            BackgroundRight(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~BackgroundRight() = default;

            // operations
            bool Update() override;
            void Move(int16_t x, int16_t y) override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_RIGHT_H_