#ifndef USERINTERFACE_PANELS_INCLUDE_RACE_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_RACE_LEFT_H_

#include <QSize>
#include "panels/Interface.h"

class QWidget;



namespace UserInterface {

    namespace Widget {

        class ScreenTitle;

    }

    namespace Panel {

        class RaceLeft final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                RaceLeft(QWidget* parent = 0);
                virtual ~RaceLeft() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

            private:
                UserInterface::Widget::ScreenTitle* m_screenTitle;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_RACE_LEFT_H_