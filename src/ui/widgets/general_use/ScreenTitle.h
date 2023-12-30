#ifndef USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_
#define USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_

#include "ScreenType.h"
#include "base/TextInterface.h"
#include "base/ID.h"



namespace UserInterface {

    namespace Widget {

        class ScreenTitle final : public UserInterface::Widget::TextInterface {

            Q_OBJECT

            public:
                ScreenTitle(UserInterface::Widget::ID id, QWidget* parent = 0);
                virtual ~ScreenTitle() = default;
                bool Update() override;
                void SetTitle(UserInterface::Screen::Type type);
        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_SCREEN_TITLE_H_