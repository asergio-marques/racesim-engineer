#ifndef USERINTERFACE_SCREENS_INCLUDE_RACE_H_
#define USERINTERFACE_SCREENS_INCLUDE_RACE_H_

#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class Race : public UserInterface::Screen::DualPanelInterface {

            Q_OBJECT

            public:
                Race(QWidget* parent = 0);
                virtual ~Race() = default;
                virtual const UserInterface::Screen::Type Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_RACE_H_