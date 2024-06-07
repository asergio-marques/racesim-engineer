#ifndef NETCOM_ADAPTERS_INCLUDE_F124_DATA_CONVERSION_MAPS_H_
#define NETCOM_ADAPTERS_INCLUDE_F124_DATA_CONVERSION_MAPS_H_

#include <map>
#include "data/internal/Session.h"
#include "data/game/F1_24/Session.h"
#include "data/game/F1_24/Participant.h"



namespace NetCom {

    namespace Adapter {

        namespace F1_24 {

            struct DataConversionMaps {

                static const std::map<Session::Game::F1_24::Track, Session::Internal::Track> TRACK_ID_MAP;
                static const std::map<Participant::Game::F1_24::TeamID, Session::Internal::TeamID> TEAM_ID_MAP;
                static const std::map<Participant::Game::F1_24::DriverID, const char*> DRIVER_SHORTHAND_MAP;

            };

        }

    }

}


#endif // NETCOM_ADAPTERS_INCLUDE_F124_DATA_CONVERSION_MAPS_H_