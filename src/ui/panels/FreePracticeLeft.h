#ifndef USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_FREE_PRACTICE_LEFT_H_

#include <QSize>
#include "base/IPanel.h"

class QWidget;



namespace UserInterface {

    namespace Widget {

        class ScreenTitle;

    }

    namespace Panel {

        class FreePracticeLeft final : public UserInterface::Base::IPanel {

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