#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_

#include "base/ImageInterface.h"
#include "data/internal/Tyre.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class TyreIcon : public UserInterface::Widget::ImageInterface {

            public:
            TyreIcon(UserInterface::Widget::ID id, QWidget* parent = 0);
            ~TyreIcon() = default;
            void SetType(Tyre::Internal::Visual type);

            private:
            bool m_isTypeSet;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_