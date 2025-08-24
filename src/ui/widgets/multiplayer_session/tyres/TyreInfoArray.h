#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/Tyre.h"




namespace UserInterface {

    namespace Widget {

        class TyreInfoContainer;

        class TyreInfoArray : public UserInterface::Widget::Container {

            public:
            TyreInfoArray(QWidget* parent = 0);
            ~TyreInfoArray() = default;
            void TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart, bool pitBeforeLine);
            void LapCompletedWithTyre();

            protected:
            void RedoDisplay();

            QList<TyreInfoContainer*> m_tyres;
            uint8_t m_stintIndex;
			static constexpr uint8_t MAX_STINTS_DISPLAY = 5;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_