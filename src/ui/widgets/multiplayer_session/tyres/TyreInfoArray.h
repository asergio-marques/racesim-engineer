#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_

#include <cstdint>
#include <QList>
#include <QWidget>
#include "data/internal/Tyre.h"



namespace UserInterface {

    namespace Widget {
        class TyreInfoContainer;

        class TyreInfoArray : public QWidget {

            public:
            TyreInfoArray(QWidget* parent = 0);
            ~TyreInfoArray() = default;
            void TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart, bool pitBeforeLine);
            void LapCompletedWithTyre();

            protected:
            void CycleLayout();

            // index 0 represents the first stint, index 1 the second, etc
            QList<TyreInfoContainer*> m_tyres;
            uint8_t m_stintIndex;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_