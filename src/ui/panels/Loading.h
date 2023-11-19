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

    namespace Widget {

        class ScreenTitle;

    }

    namespace Panel {

        class Loading final : public UserInterface::Base::IPanel {

            Q_OBJECT

            public:
                Loading(QWidget* parent = 0);
                virtual ~Loading() = default;
                virtual void ResizePanel(const QSize& newPanelSize) override final;

            private:
                UserInterface::Base::ImageElement* m_background;
                UserInterface::Base::ImageElement* m_loadingIcon;
                UserInterface::Widget::ScreenTitle* m_loadingText;

        };

    }

}

#endif // USERINTERFACE_PANELS_INCLUDE_LOADING_H_