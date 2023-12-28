#ifndef PACKETS_INTERNAL_INCLUDE_INTERFACE_H_
#define PACKETS_INTERNAL_INCLUDE_INTERFACE_H_



namespace Packet {

    namespace Internal {

        class Interface {

            public:
            // Packet interface constructor
            Interface() = default;

            // Destructor
            virtual ~Interface() = default;

        };

    }

}

#endif  //  PACKETS_INTERNAL_INCLUDE_INTERFACE_H_