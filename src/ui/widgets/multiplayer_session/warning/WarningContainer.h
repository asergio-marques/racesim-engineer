#ifndef USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_
#define USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_

#include <cstdint>
#include <QList>
#include "base/Container.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class WarningIcon;

        class WarningContainer final : public UserInterface::Widget::Container {

            public:
            enum class Type : uint8_t {

                TrackLimits = 1,
                OtherWarns = 2

            };

            WarningContainer(const UserInterface::Widget::WarningContainer::Type type, QWidget* parent = 0);
            ~WarningContainer() = default;
            void addWarning();
            virtual void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent) override final;
            void scale(const uint8_t percentX, const uint8_t percentY) override final;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override final;

            // Getters
            virtual const int16_t width() const override final;
            virtual const int16_t height() const override final;
            virtual const int16_t x() const override final;
            virtual const int16_t y() const override final;

            private:
            QList<UserInterface::Widget::WarningIcon*> m_icons;
            static constexpr uint8_t HEIGHT_SPACER = 2;
            uint8_t m_currentlyActiveWarnings;

        };
    }
}

#endif // USERINTERFACE_WIDGETS_INCLUDE_WARNING_CONTAINER_H_