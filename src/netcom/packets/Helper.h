#ifndef NETCOM_PACKETS_INCLUDE_F123_HELPER_H_
#define NETCOM_PACKETS_INCLUDE_F123_HELPER_H_

#include <cstring>

namespace F1_23 {

    namespace Packet {

        class Helper {

            public:
                Helper() = default;
                virtual ~Helper() = default;

                template<typename T>
                static void getVariableFromByteStream(char* packetInfo, T* var, size_t& movedArray) {

                    // This assumes little endian!
                    if (packetInfo) {

                        const size_t varSizeBytes = sizeof(*var);
                        char* startLoc = packetInfo + (movedArray);

                        if (startLoc && (startLoc + varSizeBytes)) {
                            std::memcpy(var, startLoc, varSizeBytes);
                            movedArray += varSizeBytes;
                        }

                    }

                }

        };

    };

};

#endif  //  NETCOM_PACKETS_INCLUDE_F123_HELPER_H_