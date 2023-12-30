#ifndef USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_
#define USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_

#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class TimeTrial : public UserInterface::Screen::DualPanelInterface {

            Q_OBJECT

            public:
                TimeTrial(QWidget* parent = 0);
                virtual ~TimeTrial() = default;
                virtual const UserInterface::Screen::Type Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_