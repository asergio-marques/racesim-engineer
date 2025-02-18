#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_

#include <QWidget>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class WarningIcon : public UserInterface::Widget::ImageInterface {

            public:
            WarningIcon(QWidget* parent = 0);
            ~WarningIcon() = default;
            void SetTrackLimitType();
            void SetOtherWarningsType();

            private:
            bool m_isTypeSet;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_