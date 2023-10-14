#ifndef USERINTERFACE_BASE_INCLUDE_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_ELEMENT_H_

#include <QWidget>
#include "base/WidgetId.h"



namespace UserInterface {

    namespace Base {

        class Element : public QWidget {

            public:
                Element(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~Element() = default;
                virtual bool Update() = 0;
                virtual const UserInterface::Base::WidgetId& GetId() const;

            private:
                UserInterface::Base::WidgetId m_id;

        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_ELEMENT_H_