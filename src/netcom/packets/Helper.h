#ifndef NETCOM_PACKETS_INCLUDE_F123_HELPER_H_
#define NETCOM_PACKETS_INCLUDE_F123_HELPER_H_

#include <cstring>
#include <exception>

#include "data/Packet.h"

namespace F1_23 {

    namespace Packet {

        class Helper {

            public:
                Helper(F1_23::Packet::LengthBytes packetLength);
                virtual ~Helper() = default;

                // Function to obtain a specific variable from a data stream, which automatically
                // moves forward the index
                template<typename T>
                void getVariableFromByteStream(char* packetInfo, T* var, size_t& movedArray) {

                    const size_t varSizeBytes = sizeof(*var);

                    // Check if the function will try to read any out-of-scope byte, and throw an error if so
                    if ((movedArray + varSizeBytes) > static_cast<size_t>(m_packetLength)) {

                        // TODO proper error handling/exception

                    }
                    else if (packetInfo) {

                        // This assumes little endian!
                        char* startLoc = packetInfo + (movedArray);
                        std::memcpy(var, startLoc, varSizeBytes);

                    }

                    // Move forward in array just in case
                    movedArray += varSizeBytes;

                    return;

                }

                // Function to obtain an array of variables of a specific type from a data stream, which automatically
                // moves forward the index
                template<typename T>
                void getVariableArrayFromByteStream(char* packetInfo, T* var, size_t numArrayMembers, size_t& movedArray) {

                    for (size_t i = 0; i < numArrayMembers; ++i) {

                        this->getVariableFromByteStream<>(packetInfo, var, movedArray);
                    
                    }

                    return;

                }

            private:
                F1_23::Packet::LengthBytes m_packetLength;

        };

    };

};

#endif  //  NETCOM_PACKETS_INCLUDE_F123_HELPER_H_