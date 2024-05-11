#ifndef USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_
#define USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_

#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class PenaltyFlag;
        class PenaltyTextBackground;
        class TextInterface;

        class PenaltyIcon : public UserInterface::Widget::Container {

            public:
            PenaltyIcon(QWidget* parent = 0);
            ~PenaltyIcon() = default;
            void addTimePenalty(const int32_t change);
            void addDriveThrough(const int32_t change);
            void addStopGo(const int32_t change);
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override;
            void scale(const uint8_t percent) override;
            void scale(const uint8_t percentX, const uint8_t percentY) override;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override;
            void raise() override final;
            void lower() override final;
            void setTextFontSize(const uint16_t size) override final;
            void adjustSize() override final;

            // Getters
            const int16_t width() const override;
            const int16_t height() const override;
            const int16_t x() const override;
            const int16_t y() const override;

            private:
            void checkDisplayStatus();
            const QString generateText();

            UserInterface::Widget::PenaltyFlag* m_flagIcon;
            UserInterface::Widget::PenaltyTextBackground* m_textBackground;
            UserInterface::Widget::TextInterface* m_text;

            // Whether this icon is active and being displayed
            bool m_active;

            // Total amount of time penalties to be served, in milliseconds
            uint32_t m_timePen;

            // Total number of drive-through penalties to be served
            uint32_t m_driveThroughs;

            // Total amount of stop-go penalties to be served
            uint32_t m_stopGos;

            static constexpr uint8_t HORIZONTAL_OFFSET = 3;
            static constexpr uint8_t VERTICAL_OFFSET = 3;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_PENALTY_ICON_H_