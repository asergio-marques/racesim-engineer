#ifndef USERINTERFACE_BASE_INCLUDE_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_ELEMENT_H_

#include <QObject>
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Base {

        class Element : public QObject {

            Q_OBJECT

            public:
                Element(UserInterface::Base::WidgetId id);
                virtual ~Element() = default;
                
                // Operations
                virtual bool Update() = 0;
                virtual void Move(const uint16_t x, const uint16_t y, const bool centerAlignment) = 0;
                virtual void Scale(const uint8_t percent) = 0;
                virtual void Scale(const uint8_t percentX, const uint8_t percentY) = 0;
                virtual const UserInterface::Base::WidgetId& GetId() const;

                // Getters
                virtual const int16_t Width() const = 0;
                virtual const int16_t Height() const = 0;

            private:
                UserInterface::Base::WidgetId m_id;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_ELEMENT_H_