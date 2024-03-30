#ifndef USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_
#define USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_

#include <QList>
#include "base/Container.h"
#include "base/packets/MPSessionStartInterface.h"



class QWidget;

namespace Packet {

    namespace Internal {

        class Interface;

    }

}

namespace UserInterface {

    namespace Widget {

        class DriverEntry;

        class Standings final : public UserInterface::Widget::Container,
            public UserInterface::Widget::MPSessionStartInterface {

            Q_OBJECT

            public:
            Standings(QWidget* parent = 0);
            virtual ~Standings() = default;
            virtual void updateAtStart(const Packet::Internal::MPSessionStart* dataPacket) override final;
            void move(const uint16_t x, const uint16_t y, const bool centerAlignmentX, const bool centerAlignmentY) override final;
            void scale(const uint8_t percent) override final;
            void scale(const uint8_t percentX, const uint8_t percentY) override final;
            void setSize(const uint16_t newWidth, const uint16_t newHeight, const bool keepAspectRatio) override final;
            void reorderStandings();
            void positionChange(const uint8_t id, const uint8_t newPosition);

            // Getters
            const int16_t width() const override final;
            const int16_t height() const override final;
            const int16_t x() const override final;
            const int16_t y() const override final;

            private:
            QWidget* m_parent;
            QList<UserInterface::Widget::DriverEntry*> m_driverData;
            bool m_initialParamsSet;


        };

    }

}

#endif // USERINTERFACE_WIDGETS_INCLUDE_STANDINGS_H_