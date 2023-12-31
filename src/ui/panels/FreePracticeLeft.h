#ifndef USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_

#include <QSize>
#include "panels/Interface.h"



class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class ScreenTitle;

    }

    namespace Panel {

        class FreePracticeLeft final : public UserInterface::Panel::Interface {

            Q_OBJECT

            public:
                FreePracticeLeft(QWidget* parent = 0);
                virtual ~FreePracticeLeft() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

            private:
                UserInterface::Widget::ScreenTitle* m_screenTitle;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_