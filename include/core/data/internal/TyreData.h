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

            // Number of the stint to which this tyre data pertains to
            uint8_t m_stintNo;

            // Number of laps completed on this tyre set (length of stint)
            uint8_t m_stintLength;

            // The visual tyre compound on which the majority of the lap was raced
            Tyre::Internal::Visual m_visualTyre;

            // The actual tyre compound on which the majority of the lap was raced
            Tyre::Internal::Actual m_actualTyre;

        };

    }

}

#endif // DATA_INTERNAL_INCLUDE_TYRE_DATA_H_