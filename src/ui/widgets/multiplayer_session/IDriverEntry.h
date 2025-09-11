#ifndef USERINTERFACE_WIDGETS_INCLUDE_IDRIVER_ENTRY_H_
#define USERINTERFACE_WIDGETS_INCLUDE_IDRIVER_ENTRY_H_

#include <cstdint>
#include <QList>
#include "base/Container.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"
#include "data/internal/Tyre.h"


class QWidget;

namespace UserInterface {

    namespace Widget {

        class Interface;

        class IDriverEntry : public UserInterface::Widget::Container {

            Q_OBJECT

            public:
            IDriverEntry();
            virtual ~IDriverEntry() = default;
            virtual void init(const Session::Internal::Participant& dataPacket) = 0;
            virtual void updatePosition(const uint8_t newPosition) {};
            virtual void updatePenalties(const Penalty::Internal::Type type, const int32_t change) {};
            virtual void updateStatus(const Participant::Internal::Status status) {};
            virtual void newSessionBestLap(const Lap::Internal::Time newLapTime, const bool isThisDrivers) {};
            virtual void newPersonalBestLap(const Lap::Internal::Time newLapTime) {};
            virtual void newLatestLap(const Lap::Internal::Time newLapTime) {};
            virtual void newTyres(const Tyre::Internal::Actual actualTyre, const Tyre::Internal::Visual visualTyre,
                const uint8_t stintNo, const uint8_t tyreAge) {};
            const uint8_t GetCurrentPosition() const;

            protected:
            QList<UserInterface::Widget::Interface*> m_allWidgets;
            uint8_t m_driverIndex;
            uint8_t m_currentPosition;
            bool m_isPlayer;

        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_IDRIVER_ENTRY_H_