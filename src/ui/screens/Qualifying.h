#ifndef USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_
#define USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_

#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class Qualifying : public UserInterface::Screen::DualPanelInterface {

            Q_OBJECT

            public:
                Qualifying(QWidget* parent = 0);
                virtual ~Qualifying() = default;
                virtual const UserInterface::Screen::Type Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_QUALIFYING_H_