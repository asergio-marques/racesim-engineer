#ifndef USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_

#include <cstdint>
#include <QWidget>
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"


class QLabel;

namespace UserInterface {

    namespace Widget {

        class FastestLapIndicator;
        class LapInfoContainer;
        class PenaltyIcon;
        class RetirementIcon;
        class TeamIcon;
        class TextInterface;
        class WarningContainer;

        class DriverEntry : public QWidget {

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

            // Getters
            const uint8_t GetCurrentPosition() const;

            private:
            QList<QWidget*> m_allWidgets;
            uint8_t m_driverIndex;
            uint8_t m_currentPosition;
            bool m_isPlayer;
            UserInterface::Widget::FastestLapIndicator* m_fastestLap;
            QLabel* m_position;
            UserInterface::Widget::WarningContainer* m_trackLimWarn;
            UserInterface::Widget::WarningContainer* m_otherWarn;
            UserInterface::Widget::TeamIcon* m_teamIcon;
            QLabel* m_driverName;
            UserInterface::Widget::LapInfoContainer* m_personalBestLap;
            UserInterface::Widget::LapInfoContainer* m_lastLap;
            UserInterface::Widget::PenaltyIcon* m_penalties;
            UserInterface::Widget::RetirementIcon* m_retirement;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_