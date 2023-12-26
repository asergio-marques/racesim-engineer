#ifndef GENERAL_PACKETS_INCLUDE_F123_HELPER_H_
#define GENERAL_PACKETS_INCLUDE_F123_HELPER_H_

#include <cstring>
#include <exception>

#include "data/F1_23/Packet.h"

namespace Packet {

    class Helper {

        public:
        Helper();
        virtual ~Helper() = default;
        inline void SetPacketLength(size_t packetLength) { m_packetLength = packetLength; }

        // Function to obtain a specific variable from a data stream, which automatically
        // moves forward the index
        template<typename T>
        void getVariableFromByteStream(const char* packetInfo, T* var, size_t& movedArray) {

            const size_t varSizeBytes = sizeof(*var);

            // Check if the function will try to read any out-of-scope byte, and throw an error if so
            if ((movedArray + varSizeBytes) > m_packetLength) {

                // TODO proper error handling/exception

            }
            else if (packetInfo) {

                // This assumes little endian!
                const char* startLoc = packetInfo + (movedArray);
                std::memcpy(var, startLoc, varSizeBytes);

            }

            // Move forward in array just in case
            movedArray += varSizeBytes;

            return;

        }

        // Function to obtain an array of variables of a specific type from a data stream, which automatically
        // moves forward the index
        template<typename T>
        void getVariableArrayFromByteStream(const char* packetInfo, T* var, size_t numArrayMembers, size_t& movedArray) {

            for (size_t i = 0; i < numArrayMembers; ++i, ++var) {

                this->getVariableFromByteStream<>(packetInfo, var, movedArray);

            }

            return;

        }

        private:
            size_t m_packetLength;

    };

};

#endif  //  GENERAL_PACKETS_INCLUDE_F123_HELPER_H_