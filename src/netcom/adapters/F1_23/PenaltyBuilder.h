#ifndef NETCOM_ADAPTERS_INCLUDE_F123_PENALTY_BUILDER_H_
#define NETCOM_ADAPTERS_INCLUDE_F123_PENALTY_BUILDER_H_

#include <vector>
#include <map>
#include <string>
#include "data/internal/Session.h"



namespace Packet {

    namespace Game {

        namespace F1_23 {

            class EventData;

        }

    }

    namespace Internal {



    }

}

namespace NetCom {

    namespace Adapter {

        class F1_23_PenaltyBuilder {

            public:
            F1_23_PenaltyBuilder();
            virtual ~F1_23_PenaltyBuilder() = default;

        };

    }

}

#endif // NETCOM_ADAPTERS_INCLUDE_F123_PENALTY_BUILDER_H_