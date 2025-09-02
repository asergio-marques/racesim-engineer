#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_

#include "base/ImageInterface.h"
#include "data/internal/Tyre.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class TyreIcon : public UserInterface::Widget::ImageInterface {

            public:
            enum class Type : uint8_t {

                Unknown     = 0,
                HyperSoft   = 1,
                SuperSoft   = 2,
                Soft        = 3,
                Medium      = 4,
                Hard        = 5,
                Inter       = 6,
                Wet         = 7

            };

            TyreIcon(UserInterface::Widget::ID id, QWidget* parent = 0);
            ~TyreIcon() = default;
            void SetType(Tyre::Internal::Visual type);

            private:
            bool m_isTypeSet;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TYRE_ICON_H_