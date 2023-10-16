#ifndef USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_H_
#define USERINTERFACE_WIDGETS_INCLUDE_BACKGROUND_H_

#include "base/elements/ImageElement.h"
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Widget {

        class Background : public UserInterface::Base::ImageElement {

            public:
            Background(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~Background() = default;
            bool Update() override;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_WIDGET_H_