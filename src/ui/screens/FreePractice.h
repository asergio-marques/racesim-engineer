#ifndef USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_
#define USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_

#include "screens/DualPanelInterface.h"
#include "core/ScreenType.h"

class QWidget;



namespace UserInterface {

    class PacketHandler;

    namespace Screen {
        class FreePractice : public UserInterface::Screen::DualPanelInterface {

            Q_OBJECT

            public:
                FreePractice(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~FreePractice() = default;
                virtual const UserInterface::Screen::Type Type() const override;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_FREE_PRACTICE_H_