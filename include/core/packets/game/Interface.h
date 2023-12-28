#ifndef PACKETS_GAME_INCLUDE_INTERFACE_H_
#define PACKETS_GAME_INCLUDE_INTERFACE_H_



namespace Packet {

    namespace Game {

        class Interface {

            public:
            // Packet interface constructor
            Interface() = default;

            // Destructor
            virtual ~Interface() = default;

            #ifndef NDEBUG
            virtual void Print() const = 0;
            #endif // NDEBUG

        };

    }

}

#endif  //  GENERAL_PACKETS_INCLUDE_IntePACKETS_INCLUDE_INTERFACE_H_rface_H_