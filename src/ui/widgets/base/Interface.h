#ifndef USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_
#define USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_

#include <QObject>
#include "base/ID.h"



namespace UserInterface {

    namespace Widget {

        class Interface : public QObject {

            Q_OBJECT

            public:
                Interface(UserInterface::Widget::ID id);
                virtual ~Interface() = default;
                
                // Operations
                virtual bool Update() = 0;
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) = 0;
                virtual const UserInterface::Widget::ID& GetId() const;

                // Getters
                virtual const int16_t Width() const = 0;
                virtual const int16_t Height() const = 0;
                virtual const int16_t X() const = 0;
                virtual const int16_t Y() const = 0;

            private:
                UserInterface::Widget::ID m_id;

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_INTERFACE_H_