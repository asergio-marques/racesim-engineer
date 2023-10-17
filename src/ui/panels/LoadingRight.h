#ifndef USERINTERFACE_PANELS_INCLUDE_LOADING_RIGHT_H_
#define USERINTERFACE_PANELS_INCLUDE_LOADING_RIGHT_H_

#include "base/IPanel.h"

class QWidget;



namespace UserInterface {

    namespace Base {

        class TextElement;
        class ImageElement;

    }

    namespace Panel {

        class LoadingRight : public UserInterface::Base::IPanel {

            public:
            LoadingRight(QWidget* parent = 0);
            virtual ~LoadingRight() = default;

            private:
            UserInterface::Base::ImageElement* m_background;
            UserInterface::Base::TextElement* m_title;
        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_LOADING_LEFT_H_