#ifndef DATA_INTERNAL_INCLUDE_TYRE_DATA_H_
#define DATA_INTERNAL_INCLUDE_TYRE_DATA_H_

#include <cstdint>
#include "data/internal/Tyre.h"



namespace Tyre {

    namespace Internal {

        struct Data {

            public:
            Data();

            Data& operator=(const Data& other);
            bool operator==(const Data& other);
            bool operator!=(const Data& other);

            // Whether the ID of the tyre set in use for the majority of the lap has been initialized
            bool m_hasID;

            // ID of the tyre set on which the majority of the lap was raced
            uint8_t m_setID;

            // The visual tyre compound on which the majority of the lap was raced
            Tyre::Internal::Visual m_visualTyre;

            // The actual tyre compound on which the majority of the lap was raced
            Tyre::Internal::Actual m_actualTyre;

            // Whether the age of the tyre set in use for the majority of the lap has been initialized
            bool m_hasAge;

            // Number of laps done on the tyre set on which the majority of the lap was raced
            uint8_t m_ageLaps;

        };

    }

}

#endif // DATA_INTERNAL_INCLUDE_TYRE_DATA_H_