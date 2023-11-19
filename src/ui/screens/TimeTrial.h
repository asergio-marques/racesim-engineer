#ifndef USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_
#define USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_

#include "base/IDualPanelScreen.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class TimeTrial : public UserInterface::Base::IDualPanelScreen {

            Q_OBJECT

        public:
            TimeTrial(QWidget* parent = 0);
            virtual ~TimeTrial() = default;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_