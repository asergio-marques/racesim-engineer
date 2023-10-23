#ifndef USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_
#define USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_

#include "base/WidgetId.h"
#include "base/Element.h"

class QLabel;
class QWidget;



namespace UserInterface {

    namespace Base {

        class ImageElement : public UserInterface::Base::Element {

            Q_OBJECT

            public:
                ImageElement(UserInterface::Base::WidgetId id, QWidget* parent = 0);
                virtual ~ImageElement() = default;

                // Getters
                virtual const int16_t Width() const override;
                virtual const int16_t Height() const override;

            protected:
                QLabel* m_image;
        };

    }

}

#endif // USERINTERFACE_BASE_INCLUDE_IMAGE_ELEMENT_H_