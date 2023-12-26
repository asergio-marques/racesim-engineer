#ifndef PACKETS_GAME_F123_INCLUDE_TYRE_SET_DATA_H_
#define PACKETS_GAME_F123_INCLUDE_TYRE_SET_DATA_H_

#include <cstdint>
#include "data/F1_23/Packet.h"
#include "data/F1_23/Session.h"
#include "data/F1_23/Status.h"
#include "packets/game/F1_23/Interface.h"

namespace Packet {

    namespace Game {

        class Helper;

        namespace F1_23 {

            class Header;

            struct TyreSetInfo {

                // Actual tyre compound of the set
                Status::F1_23::ActualTyreCompound m_actualTyreCompound;

                // Visual tyre compound of the set
                Status::F1_23::VisualTyreCompound m_visualTyreCompound;

                // Tyre wear (percentage)
                uint8_t m_wear;

                // Whether this set is currently available
                bool m_available;

                // Recommended session for tyre set
                Session::F1_23::Type m_recommendedSession;

                // Average laps left in the tyre set
                uint8_t m_currentRemainingLifeSpan;

                // Maximum number of laps recommended for this compound
                uint8_t m_usableLifeSpan;

                // Lap time delta compared to fitted set (milliseconds, 0 if fitted)
                int16_t m_lapDeltaTime;

                // Whether the set is fitted or not
                bool m_fitted;

            };

            class TyreSetData final : public Packet::Game::F1_23::Interface {

                public:
                TyreSetData(const char* packetInfo, const Header* header, Packet::Game::Helper* helper);
                ~TyreSetData() = default;

                // Returns the length of the packet in bytes, including header
                const Packet::Game::F1_23::LengthBytes GetLength() const override;

                // Getters for packet info
                const uint8_t GetCarIndex() const { return m_carIndex; }
                const uint8_t GetFittedSetIndex() const { return m_fittedSetIndex; }
                const Packet::Game::F1_23::TyreSetInfo* const GetTyreSetInfo() const { return m_tyreSets; }

                #ifndef NDEBUG
                void Print() const override;
                #endif // NDEBUG

                private:
                // Separate function to build the packet, making the code more readable
                void BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) override final;

                // Index of the vehicle this data relates to
                uint8_t m_carIndex;

                // Index of the tyre set that is currently fitted on this car
                uint8_t m_fittedSetIndex;

                // Tyre set data for this car
                // First 13 array members are dry compound tyres, following 7 are wet compound tyres
                TyreSetInfo m_tyreSets[20];

            };

        }

    }

}

#endif  // PACKETS_GAME_F123_INCLUDE_TYRE_SET_DATA_H_