#ifndef GENERALIZER_MAPS_INCLUDE_F1_25_H_
#define GENERALIZER_MAPS_INCLUDE_F1_25_H_

#include <map>
#include "data/internal/Session.h"
#include "data/internal/Tyre.h"
#include "data/game/F1_25/Participant.h"
#include "data/game/F1_25/Session.h"
#include "data/game/F1_25/Status.h"



namespace Generalizer {

	namespace Maps {

		struct F1_25 {

			static const std::map<Session::Game::F1_25::Track, Session::Internal::Track> TRACK_ID_MAP;
			static const std::map<Participant::Game::F1_25::TeamID, Session::Internal::TeamID> TEAM_ID_MAP;
			static const std::map<Participant::Game::F1_25::DriverID, const char*> DRIVER_SHORTHAND_MAP;
			static const std::map<Status::Game::F1_25::ActualTyreCompound, Tyre::Internal::Actual> ACTUAL_TYRE_MAP;
			static const std::map<Status::Game::F1_25::VisualTyreCompound, Tyre::Internal::Visual> VISUAL_TYRE_MAP;


		};

	}

}


#endif // GENERALIZER_MAPS_INCLUDE_F1_25_H_