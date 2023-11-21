#ifndef USERINTERFACE_SCREENS_INCLUDE_LOADING_H_
#define USERINTERFACE_SCREENS_INCLUDE_LOADING_H_

#include "base/ISinglePanelScreen.h"
#include "base/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Base {

        class TextElement;
        class ImageElement;

    }

    namespace Screen {

        class Loading : public UserInterface::Base::ISinglePanelScreen {

            Q_OBJECT

        public:
            Loading(QWidget* parent = 0);
            virtual ~Loading() = default;
            virtual const UserInterface::Base::ScreenType Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_LOADING_H_