#ifndef USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_

#include <QObject>
#include "base/ID.h"



namespace UserInterface {

    namespace Widget {

        class Interface {

            public:
                Interface(UserInterface::Widget::ID id);
                virtual ~Interface() = default;
                virtual void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) = 0;
                virtual const UserInterface::Widget::ID& GetId() const;

            protected:
                UserInterface::Widget::ID m_id;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_