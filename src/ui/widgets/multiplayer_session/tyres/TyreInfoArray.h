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
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
            void scale(const uint8_t percent) override;
            void scale(const uint8_t percentX, const uint8_t percentY) override;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            void raise() override;
            void lower() override;
            const int16_t width() const override;
            const int16_t height() const override;
            const int16_t x() const override;
            const int16_t y() const override;
            void TyreChange(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart, bool pitBeforeLine);
            void LapCompletedWithTyre();

            protected:
            void RedoDisplay();

			QWidget* m_widgetParent;
            QList<TyreInfoContainer*> m_tyres;
            uint8_t m_stintIndex;
			static constexpr uint8_t MAX_STINTS_DISPLAY = 5;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_ARRAY_H_