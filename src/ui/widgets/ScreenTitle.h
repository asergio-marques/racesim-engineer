#ifndef USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_

#include "base/elements/TextElement.h"
#include "base/WidgetId.h"


namespace UserInterface {

    namespace Widget {

        enum class ScreenType {

            InvalidUnknown  = 0,
            Loading         = 1,
            FreePractice    = 2,
            TimeTrial       = 3,
            Qualification   = 4,
            Race            = 5

        };

        class ScreenTitle final : public UserInterface::Base::TextElement {

            Q_OBJECT

            public:
                ScreenTitle(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~ScreenTitle() = default;
                bool Update() override;
                void SetTitle(UserInterface::Widget::ScreenType type);
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_