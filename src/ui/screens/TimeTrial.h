#ifndef USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_
#define USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_

#include <QSharedPointer>
#include "screens/DualPanelInterface.h"
#include "core/Screen.h"

class QWidget;




namespace UserInterface {

    class PacketHandler;

    namespace Screen {

        class TimeTrial : public UserInterface::Screen::DualPanelInterface {

            Q_OBJECT

            public:
                TimeTrial(UserInterface::PacketHandler* handler, QWidget* parent = 0);
                virtual ~TimeTrial() = default;
                virtual const UserInterface::Screen::Type Type() const override;
                void Activate(QSharedPointer<const Packet::Event::Interface> startupInfo) override final;

        };

    }

}

#endif // USERINTERFACE_SCREENS_INCLUDE_TIME_TRIAL_H_