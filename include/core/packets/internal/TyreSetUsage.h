#ifndef PACKETS_INTERNAL_INCLUDE_TYRE_SET_USAGE_H_
#define PACKETS_INTERNAL_INCLUDE_TYRE_SET_USAGE_H_

#include <cstdint>
#include <vector>
#include "data/internal/Tyre.h"
#include "packets/internal/Interface.h"
#include "packets/internal/Type.h"



namespace Packet {

    namespace Internal {

        struct TyreSetUsage : public Packet::Internal::Interface {

            struct Data {

                public:
                // Constructor
                Data();

                // ID of the driver for which this standing is relative to
                uint8_t m_driverID;

                // ID of the tyre set current in use by this participant's car
                uint8_t m_tyreSetID;

                // Actual compound of all tyres currently in use by this participant's car
                Tyre::Internal::Actual m_actualTyreCompound;

                // Visual compound of all tyres currently in use by this participant's car
                Tyre::Internal::Visual m_visualTyreCompound;

            };

            public:
            // Packet constructor
            TyreSetUsage(const uint64_t timestamp);

            // Destructor
            virtual ~TyreSetUsage() = default;

            // Type identifier for the packet
            const Packet::Internal::Type packetType() const override final;

            // Adds grid position data into the packet
            void InsertData(const Packet::Internal::TyreSetUsage::Data& data);

            // Retrieve grid position data from the packet
            const std::vector<Packet::Internal::TyreSetUsage::Data>& GetData() const;

            private:
            // Holds the grid position of all drivers in the session
            std::vector<Packet::Internal::TyreSetUsage::Data> m_fullData;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_TYRE_SET_USAGE_H_