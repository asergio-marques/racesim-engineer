#ifndef USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_

#include "base/WidgetId.h"
#include "base/Element.h"

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Base {

        class TextElement : public UserInterface::Base::Element {

            public:
            TextElement(UserInterface::Base::WidgetId id, QWidget* parent = 0);
            virtual ~TextElement() = default;

            protected:
            QLabel* m_text;
        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_TEXT_ELEMENT_H_