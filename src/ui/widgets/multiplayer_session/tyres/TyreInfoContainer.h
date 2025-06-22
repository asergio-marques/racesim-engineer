#ifndef USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_TYRE_INFO_CONTAINER_H_

#include <cstdint>
#include "base/Container.h"
#include "data/internal/Tyre.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class TextInterface;
        class TyreIcon;

        class TyreInfoContainer : public UserInterface::Widget::Container {

            public:
            TyreInfoContainer(QWidget* parent = 0);
            ~TyreInfoContainer() = default;
            void Init(Tyre::Internal::Actual actualTyreCompound, Tyre::Internal::Visual visualTyreCompound, uint8_t numLapsAtStart);
            void IncrementLap();
            virtual void scale(const uint8_t percentX, const uint8_t percentY) override;
            virtual void scale(const uint8_t percent) override;
            virtual void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            virtual void raise(void) override;
            virtual void lower(void) override;
            virtual void setTextFontSize(const uint16_t size) override;
            virtual const int16_t width(void) const override;
            virtual const int16_t height(void) const override;
            virtual const int16_t x(void) const override;
            virtual const int16_t y(void) const override;
            virtual void move(const uint16_t x, const uint16_t y, const bool centerX, const bool centerY) override;

            protected:
            UserInterface::Widget::TyreIcon* m_visualCompoundIcon;
            UserInterface::Widget::TextInterface* m_actualCompoundText;
            UserInterface::Widget::TextInterface* m_lapsText;
            uint8_t m_numLaps;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_TIME_INFO_CONTAINER_H_