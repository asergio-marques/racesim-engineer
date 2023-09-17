#ifndef NETCOM_PACKET_BUILDERS_INCLUDE_F123_HEADER_H_
#define NETCOM_PACKET_BUILDERS_INCLUDE_F123_HEADER_H_

namespace F1_23 {

    namespace Packet {

        class Header;

    }

    namespace PacketBuilder {

        class Header {

            public:
                Header();
                virtual ~Header() = default;

                F1_23::Packet::Header* buildNewHeader(char* packetInfo) const;

            /*private:
                template<typename T>
                void getVariable(char* packetInfo, T& var, size_t& movedArray) const {
                
                    for (uint8_t i = 0; i < sizeof(var); ++i, ++movedArray) {

                        var += packetInfo[movedArray] << (8 * (sizeof(var) - i - 1));

                    }
                
                }
            */
        };

    };

};

#endif  //  NETCOM_PACKET_BUILDERS_INCLUDE_F123_HEADER_H_