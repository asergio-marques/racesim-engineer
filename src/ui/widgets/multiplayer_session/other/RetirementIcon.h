#ifndef USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_

#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class RetirementIconBackground;
        class TextInterface;

        class RetirementIcon : public UserInterface::Widget::Container {

            public:
            RetirementIcon(QWidget* parent = 0);
            ~RetirementIcon() = default;
            void activate();
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
            void scale(const uint8_t percent) override;
            void scale(const uint8_t percentX, const uint8_t percentY) override;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            const int16_t width() const override;
            const int16_t height() const override;
            const int16_t x() const override;
            const int16_t y() const override;
            void setTextFontSize(const uint16_t size) override;
            void adjustSize() override;

            UserInterface::Widget::RetirementIconBackground* m_background;
            UserInterface::Widget::TextInterface* m_text;

            static constexpr uint8_t HORIZONTAL_OFFSET = 3;
            static constexpr uint8_t VERTICAL_OFFSET = 3;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_RETIREMENT_ICON_H_