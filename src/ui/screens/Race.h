#ifndef USERINTERFACE_SCREENS_INCLUDE_RACE_H_
#define USERINTERFACE_SCREENS_INCLUDE_RACE_H_

#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class Race : public UserInterface::Base::IDualPanelScreen {

            Q_OBJECT

            public:
                Race(QWidget* parent = 0);
                virtual ~Race() = default;
                virtual const UserInterface::Base::ScreenType Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_RACE_H_