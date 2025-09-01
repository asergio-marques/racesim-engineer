#ifndef PACKETS_EVENT_INCLUDE_INTERFACE_H_
#define PACKETS_EVENT_INCLUDE_INTERFACE_H_

#include <cstdint>
#include <string>
#include "packets/event/Type.h"



namespace Packet {

    namespace Event {

        class Interface {

            public:
            // Packet interface constructor, default
            Interface();

            // Packet interface constructor for packets that are meant to be used for TTS announcement
            Interface(const bool isPlayer, const std::string fullName, const uint8_t currentPosition);

            // Destructor
            virtual ~Interface() = default;

            // Type identifier for the packet, to be overridden
            virtual const Packet::Event::Type packetType() const = 0;

            // Denotes if this packet has been fully processed and if it can be deleted
            virtual inline const bool isProcessed() const;

            // Marks this packet has having been fully processed
            virtual inline void markAsProcessed();

            // Whether the participant to which this packet refers is the player, useful to filter TTS announcements
            const bool m_isPlayer;

            // Full name of the participant to which this packet refers, useful for TTS announcement
            const std::string m_fullName;

            // Current position of the participant to which this packet refers, useful for TTS announcement
            const uint8_t m_currentPosition;

            private:
            // Whether the packet has been processed
            bool m_processed;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_INTERFACE_H_