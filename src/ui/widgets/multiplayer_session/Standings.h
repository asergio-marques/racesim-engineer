#ifndef USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_
#define USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_

#include <cstdint>
#include <QMap>
#include <QSharedPointer>
#include "base/Container.h"
#include "packets/event/LapFinished.h"
#include "packets/event/Overtake.h"
#include "packets/event/ParticipantStatusChanged.h"
#include "packets/event/PenaltyReceived.h"
#include "packets/event/PracticeStart.h"
#include "packets/event/QualiStart.h"
#include "packets/event/QualiSync.h"
#include "packets/event/RaceStart.h"
#include "packets/event/RaceSync.h"
#include "packets/event/SectorStateChanged.h"
#include "packets/event/TimeTrialStart.h"
#include "packets/event/TyreChanged.h"



class QWidget;

namespace UserInterface {

    namespace Widget {

        class IDriverEntry;

        class Standings final : public UserInterface::Widget::Container {

            Q_OBJECT

            public:
            Standings(QWidget* parent = 0);
            virtual ~Standings() = default;
            void cleanup();
            void onQualiStart(QSharedPointer<Packet::Event::QualiStart> dataPacket);
            void onRaceStart(QSharedPointer<Packet::Event::RaceStart> dataPacket);
            void onQualiSync(QSharedPointer<Packet::Event::QualiSync> dataPacket);
            void onRaceSync(QSharedPointer<Packet::Event::RaceSync> dataPacket);
            void onOvertake(QSharedPointer<Packet::Event::Overtake> dataPacket);
            void onPenaltyReceived(QSharedPointer<Packet::Event::PenaltyReceived> dataPacket);
            void onParticipantStatusChanged(QSharedPointer<Packet::Event::ParticipantStatusChanged> dataPacket);
            void onLapFinished(QSharedPointer<Packet::Event::LapFinished> dataPacket);
            void onTyreChanged(QSharedPointer<Packet::Event::TyreChanged> dataPacket);
            void onSectorStateChanged(QSharedPointer<Packet::Event::SectorStateChanged> dataPacket);
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
            void reorderStandings();
            void doLapFinished(UserInterface::Widget::IDriverEntry* entry, Lap::Internal::InfoType type, Lap::Internal::Time time);

            QWidget* m_parent;
            QMap<const uint8_t, UserInterface::Widget::IDriverEntry*> m_driverData;
            UserInterface::Widget::IDriverEntry* m_currentFastestLapHolder;
            bool m_initialParamsSet;


        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_