#ifndef USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_
#define USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_

#include <QList>
#include <QWidget>
#include "packets/internal/multi_use/MPSessionStart.h"
#include "packets/internal/multi_use/ParticipantStatusChange.h"
#include "packets/internal/multi_use/PenaltyChange.h"
#include "packets/internal/multi_use/FinishedLapInfo.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class DriverEntry;

        class Standings final : public QWidget {

            Q_OBJECT

            public:
            Standings(QWidget* parent = 0);
            virtual ~Standings() = default;
            void reorderStandings();
            void positionChange(const uint8_t id, const uint8_t newPosition);
            void setStartingGrid(const Packet::Internal::MPSessionStart* dataPacket);
            void penaltyAssignedToVehicle(const Packet::Internal::PenaltyChange* dataPacket);
            void vehicleStatusChanged(const Packet::Internal::ParticipantStatusChange* dataPacket);
            void newCompletedLapInfo(const Packet::Internal::FinishedLapInfo* dataPacket);

            private:
            QList<UserInterface::Widget::DriverEntry*> m_driverData;
            UserInterface::Widget::DriverEntry* m_currentFastestLapHolder;
            bool m_initialParamsSet;


        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_