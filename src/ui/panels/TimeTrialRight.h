#ifndef USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_RIGHT_H_

#include <QSize>
#include "panels/Interface.h"



class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Panel {

        class TimeTrialRight final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                TimeTrialRight(QWidget* parent = 0);
                virtual ~TimeTrialRight() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_TIME_TRIAL_RIGHT_H_