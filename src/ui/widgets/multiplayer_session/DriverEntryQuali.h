#ifndef USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_QUALI_H_
#define USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_QUALI_H_

#include <cstdint>
#include "base/Container.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "data/internal/Tyre.h"
#include "multiplayer_session/IDriverEntry.h"


class QWidget;

namespace UserInterface {

    namespace Widget {

        class LapInfoContainer;
        class TeamIcon;
        class TextInterface;

        class DriverEntryQuali : public UserInterface::Widget::IDriverEntry {

            Q_OBJECT

            public:
            DriverEntryQuali(QWidget* parent = 0);
            virtual ~DriverEntryQuali() = default;
            void init(const Session::Internal::Participant& dataPacket);
            void updatePosition(const uint8_t newPosition);
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

            private:
            void redoLayout() override final;
            UserInterface::Widget::TextInterface* m_position;
            UserInterface::Widget::TeamIcon* m_teamIcon;
            UserInterface::Widget::TextInterface* m_driverName;
            UserInterface::Widget::LapInfoContainer* m_personalBestLap;
            UserInterface::Widget::LapInfoContainer* m_lastLap;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_QUALI_H_