#ifndef USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_

#include <cstdint>
#include "base/Container.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"


class QWidget;

namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator;
        class TeamIcon;
        class TextInterface;
        class PenaltyIcon;
        class WarningContainer;

        class DriverEntry : public UserInterface::Widget::Container {

            Q_OBJECT

            public:
            DriverEntry(QWidget* parent = 0);
            virtual ~DriverEntry() = default;
            virtual void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent) override final;
            void scale(const uint8_t percentX, const uint8_t percentY) override final;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override final;
            void init(const Session::Internal::Participant& dataPacket, const uint8_t& initPosition);
            void updatePosition(const uint8_t newPosition);
            void updatePenalties(const Penalty::Internal::Type type, const int32_t change);

            // Getters
            virtual const int16_t width() const override final;
            virtual const int16_t height() const override final;
            virtual const int16_t x() const override final;
            virtual const int16_t y() const override final;
            const uint8_t GetCurrentPosition() const;

            private:
            QList<UserInterface::Widget::Interface*> m_allWidgets;
            uint8_t m_driverIndex;
            uint8_t m_currentPosition;
            bool m_isPlayer;
            UserInterface::Widget::FastestLapIndicator* m_fastestLap;
            UserInterface::Widget::TextInterface* m_position;
            UserInterface::Widget::TeamIcon* m_teamIcon;
            UserInterface::Widget::TextInterface* m_driverName;
            UserInterface::Widget::PenaltyIcon* m_penalties;
            UserInterface::Widget::WarningContainer* m_trackLimWarn;
            UserInterface::Widget::WarningContainer* m_otherWarn;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_