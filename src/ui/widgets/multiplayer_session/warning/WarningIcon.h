#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_

#include <QLabel>



class QWidget;

namespace UserInterface {

    namespace Widget {

        class WarningIcon : public QLabel {

            public:
            WarningIcon(QWidget* parent = 0);
            ~WarningIcon() = default;
            void SetTrackLimitType();
            void SetOtherWarningsType();

            private:
            QPixmap m_pixmap;
            bool m_isTypeSet;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_ICON_H_