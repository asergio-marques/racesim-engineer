#ifndef USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_

#include <cstdint>
#include "base/Container.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"


class QWidget;

namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator;
        class LapInfoContainer;
        class PenaltyIcon;
        class RetirementIcon;
        class TeamIcon;
        class TextInterface;
        class TyreInfoArray;
        class WarningContainer;

        class DriverEntry : public UserInterface::Widget::Container {

            Q_OBJECT

            public:
            DriverEntry(QWidget* parent = 0);
            virtual ~DriverEntry() = default;
            void init(const Session::Internal::Participant& dataPacket, const uint8_t& initPosition);
            void updatePosition(const uint8_t newPosition);
            void updatePenalties(const Penalty::Internal::Type type, const int32_t change);
            void updateStatus(const Participant::Internal::Status status);
            void newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers);
            void newPersonalBestLap(const Lap::Internal::Time newLapTime);
            void newLatestLap(const Lap::Internal::Time newLapTime);
            virtual void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent) override final;
            void scale(const uint8_t percentX, const uint8_t percentY) override final;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override final;
            void raise() override final;
            void lower() override final;

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
            UserInterface::Widget::WarningContainer* m_trackLimWarn;
            UserInterface::Widget::WarningContainer* m_otherWarn;
            UserInterface::Widget::TeamIcon* m_teamIcon;
            UserInterface::Widget::TextInterface* m_driverName;
            UserInterface::Widget::LapInfoContainer* m_personalBestLap;
            UserInterface::Widget::LapInfoContainer* m_lastLap;
            UserInterface::Widget::TyreInfoArray* m_tyreArray;
            UserInterface::Widget::PenaltyIcon* m_penalties;
            UserInterface::Widget::RetirementIcon* m_retirement;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_