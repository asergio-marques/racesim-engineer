#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_

#include <QList>
#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class WarningIcon;

        class WarningContainer : public UserInterface::Widget::Container {

            public:
            WarningContainer(QWidget* parent = 0);
            ~WarningContainer() = default;

            private:
            QList<UserInterface::Widget::WarningIcon*> m_icons;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_