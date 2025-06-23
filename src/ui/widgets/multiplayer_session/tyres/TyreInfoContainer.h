#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_

#include <cstdint>
#include <QWidget>
#include "data/internal/Tyre.h"



namespace UserInterface {

    namespace Widget {

        class TextInterface;
        class TyreIcon;

        class TyreInfoContainer : public QWidget {

            public:
            TyreInfoContainer(QWidget* parent = 0);
            ~TyreInfoContainer() = default;
            void Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart);
            void IncrementLap();

            protected:
            UserInterface::Widget::TyreIcon* m_visualCompoundIcon;
            UserInterface::Widget::TextInterface* m_actualCompoundText;
            UserInterface::Widget::TextInterface* m_lapsText;
            uint8_t m_numLaps;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_