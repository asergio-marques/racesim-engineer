#ifndef USERINTERFACE_PANELS_INCLUDE_LOADING_LEFT_H_
#define USERINTERFACE_PANELS_INCLUDE_LOADING_LEFT_H_

#include "base/IPanel.h"

class QWidget;



namespace UserInterface {

    namespace Base {

        class TextElement;
        class ImageElement;

    }

    namespace Panel {

        class LoadingLeft : public UserInterface::Base::IPanel {

            public:
                LoadingLeft(QWidget* parent = 0);
                virtual ~LoadingLeft() = default;

            private:
                UserInterface::Base::ImageElement* m_background;
                UserInterface::Base::ImageElement* m_loadingIcon;
                UserInterface::Base::TextElement* m_title;
        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_LOADING_LEFT_H_