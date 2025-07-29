#ifndef USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_DRIVER_ENTRY_H_

#include <cstdint>
#include <QWidget>
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"


class QGridLayout;

namespace UserInterface {

    namespace Widget {

        class LapInfoContainer;
        class PenaltyIcon;
        class PositionMultiIndicator;
        class RetirementIcon;
        class TeamIcon;
        class TextInterface;
        class TyreInfoArray;

        class DriverEntry : public QWidget {

            Q_OBJECT

            public:
            DriverEntry(QWidget* parent = 0);
            virtual ~DriverEntry() = default;
            void init(const Session::Internal::Participant& dataPacket);
            void updatePosition(const uint8_t newPosition);
            void updatePenalties(const Penalty::Internal::Type type, const int32_t change);
            void updateStatus(const Participant::Internal::Status status);
            void newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers);
            void newPersonalBestLap(const Lap::Internal::Time newLapTime);
            void newLatestLap(const Lap::Internal::Time newLapTime);
            const uint8_t GetCurrentPosition() const;

            private:
            QGridLayout* m_layout;
            uint8_t m_driverIndex;
            bool m_isPlayer;
            UserInterface::Widget::PositionMultiIndicator* m_posIndicator;
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