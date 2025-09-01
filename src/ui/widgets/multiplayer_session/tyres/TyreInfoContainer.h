#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_

#include <cstdint>
#include "base/Container.h"
#include "data/internal/Tyre.h"



namespace UserInterface {

    namespace Widget {

        class TextInterface;
        class TyreIcon;

        class TyreInfoContainer : public UserInterface::Widget::Container {

            public:
            TyreInfoContainer(QWidget* parent = 0);
            ~TyreInfoContainer() = default;
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

            void Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart);
            void IncrementLap();
            void Show();
            void Hide();
            void RedoneOnce();
            bool HasBeenRedoneAtLeastOnce() const;

            protected:
            UserInterface::Widget::TyreIcon* m_visualCompoundIcon;
            UserInterface::Widget::TextInterface* m_actualCompoundText;
            UserInterface::Widget::TextInterface* m_lapsText;
            uint8_t m_numLaps;
            bool m_redone;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_