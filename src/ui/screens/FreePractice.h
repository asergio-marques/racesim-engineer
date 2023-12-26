#ifndef USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_
#define USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_

#include "base/IDualPanelScreen.h"
#include "base/ScreenType.h"

class QWidget;



namespace UserInterface {

    namespace Screen {

        class FreePractice : public UserInterface::Base::IDualPanelScreen {

            Q_OBJECT

            public:
                FreePractice(QWidget* parent = 0);
                virtual ~FreePractice() = default;
                virtual const UserInterface::Base::ScreenType Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_