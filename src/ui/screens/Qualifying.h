#ifndef USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_
#define USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_

#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class Qualifying : public UserInterface::Base::IDualPanelScreen {

            Q_OBJECT

            public:
                Qualifying(QWidget* parent = 0);
                virtual ~Qualifying() = default;
                virtual const UserInterface::Base::ScreenType Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_