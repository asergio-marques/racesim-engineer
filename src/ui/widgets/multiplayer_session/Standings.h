#ifndef USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_
#define USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_

#include <QList>
#include "base/Container.h"
#include "packets/event/LapFinished.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/RaceStart.h"
#include "packets/event/TimeTrialStart.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class DriverEntry;

        class Standings final : public UserInterface::Widget::Container {

            Q_OBJECT

            public:
            Standings(QWidget* parent = 0);
            virtual ~Standings() = default;
            void reorderStandings();
            void positionChange(const uint8_t id, const uint8_t newPosition);
            void setStartingGrid(const Packet::Event::RaceStart* dataPacket);
            void onPenaltyReceived(const Packet::Event::PenaltyReceived* dataPacket);
            void onParticipantStatusChanged(const Packet::Event::ParticipantStatusChanged* dataPacket);
            void onLapFinished(const Packet::Event::LapFinished* dataPacket);
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent) override final;
            void scale(const uint8_t percentX, const uint8_t percentY) override final;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override final;
            void raise() override final;
            void lower() override final;

            // Getters
            const int16_t width() const override final;
            const int16_t height() const override final;
            const int16_t x() const override final;
            const int16_t y() const override final;

            private:
            QWidget* m_parent;
            QList<UserInterface::Widget::DriverEntry*> m_driverData;
            UserInterface::Widget::DriverEntry* m_currentFastestLapHolder;
            bool m_initialParamsSet;


        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_