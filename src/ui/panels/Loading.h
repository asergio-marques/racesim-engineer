#ifndef USERINTERFACE_PANELS_INCLUDE_LOADING_H_
#define USERINTERFACE_PANELS_INCLUDE_LOADING_H_

#include "base/IPanel.h"

class QResizeEvent;
class QWidget;



namespace UserInterface {

    namespace Base {

        class TextElement;
        class ImageElement;

    }

    namespace Panel {

        class Loading : public UserInterface::Base::IPanel {

            Q_OBJECT

            public:
                Loading(QWidget* parent = 0);
                virtual ~Loading() = default;

            protected:
                virtual void resizeEvent(QResizeEvent* event) override final;

            private:
                UserInterface::Base::ImageElement* m_background;
                UserInterface::Base::ImageElement* m_loadingIcon;
        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_LOADING_H_