#ifndef NETCOM_PACKET_BUILDERS_INCLUDE_F123_HELPER_H_
#define NETCOM_PACKET_BUILDERS_INCLUDE_F123_HELPER_H_

#include <type_traits>
#include <cstdint>
#include <math.h>

namespace F1_23 {

    namespace PacketBuilder {

        class Helper {

            public:
                Helper() = default;
                virtual ~Helper() = default;
            
                template<typename T>
                static typename std::enable_if<std::is_unsigned<T>::value, void>::type getVariable(char* packetInfo, T& var, size_t& movedArray) {

                    for (uint8_t i = 0; i < sizeof(var); ++i, ++movedArray) {

                        uint8_t shiftBits = (8 * (sizeof(var) - i - 1));
                        var += static_cast<uint8_t>(packetInfo[movedArray]) << shiftBits;

                    }

                    PrintDebugInfo(var, movedArray);

                }

                template<typename T>
                static typename std::enable_if<std::is_signed<T>::value, void>::type getVariable(char* packetInfo, T& var, size_t& movedArray) {

                    // TODO implement

                    for (uint8_t i = 0; i < sizeof(var); ++i, ++movedArray) {

                        uint8_t shiftBits = (8 * (sizeof(var) - i - 1));
                        var += static_cast<int8_t>(packetInfo[movedArray]) << shiftBits;

                    }

                    PrintDebugInfo(var, movedArray);

                }

                template<>
                static void getVariable<bool>(char* packetInfo, bool& var, size_t& movedArray) {

                    if (packetInfo[movedArray] > 1U) { var = true; }
                    else { var = false; }
                    
                    ++movedArray;

                    PrintDebugInfo(var, movedArray);

                }

                template<>
                static void getVariable<float_t>(char* packetInfo, float_t& var, size_t& movedArray) {

                    // TODO implement

                    PrintDebugInfo(var, movedArray);

                }

                template<>
                static void getVariable<double_t>(char* packetInfo, double_t& var, size_t& movedArray) {

                    // TODO implement

                    PrintDebugInfo(var, movedArray);

                }

                template<typename T>
                static void PrintDebugInfo(const T& var, const size_t& movedArray) {
    
                    std::cout << "\tPost-processing output: " << var << std::endl;
                    std::cout << "\tPost-processing array status: " << movedArray << std::endl;
                
                }

        };

    };

};

#endif  //  NETCOM_PACKET_BUILDERS_INCLUDE_F123_HELPER_H_