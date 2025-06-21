#include "adapters/F1_25/DataConversionMaps.h"

#include <map>
#include "data/internal/Session.h"
#include "data/game/F1_25/Session.h"
#include "data/game/F1_25/Participant.h"



const std::map<Session::Game::F1_25::Track, Session::Internal::Track>
NetCom::Adapter::F1_25::DataConversionMaps::TRACK_ID_MAP = {
    { Session::Game::F1_25::Track::InvalidUnknown           , Session::Internal::Track::Unknown },
    { Session::Game::F1_25::Track::AUS_Melbourne            , Session::Internal::Track::AUS_Melbourne },
    { Session::Game::F1_25::Track::CHI_Shanghai             , Session::Internal::Track::CHI_Shanghai },
    { Session::Game::F1_25::Track::BAH_Sakhir               , Session::Internal::Track::BAH_Sakhir },
    { Session::Game::F1_25::Track::SPA_Catalunya            , Session::Internal::Track::SPA_Catalunya },
    { Session::Game::F1_25::Track::MON_Monaco               , Session::Internal::Track::MON_Monaco },
    { Session::Game::F1_25::Track::CAN_Montreal             , Session::Internal::Track::CAN_Montreal },
    { Session::Game::F1_25::Track::ENG_Silverstone          , Session::Internal::Track::ENG_Silverstone },
    { Session::Game::F1_25::Track::HUN_Hungaroring          , Session::Internal::Track::HUN_Hungaroring },
    { Session::Game::F1_25::Track::BEL_Spa                  , Session::Internal::Track::BEL_Spa },
    { Session::Game::F1_25::Track::ITA_Monza                , Session::Internal::Track::ITA_Monza },
    { Session::Game::F1_25::Track::SNG_Singapore            , Session::Internal::Track::SNG_Singapore },
    { Session::Game::F1_25::Track::JAP_Suzuka               , Session::Internal::Track::JAP_Suzuka },
    { Session::Game::F1_25::Track::UAE_AbuDhabi             , Session::Internal::Track::UAE_AbuDhabi },
    { Session::Game::F1_25::Track::USA_Texas                , Session::Internal::Track::USA_Texas },
    { Session::Game::F1_25::Track::BRA_Interlagos           , Session::Internal::Track::BRA_Interlagos },
    { Session::Game::F1_25::Track::AUT_RedBullRing          , Session::Internal::Track::AUT_RedBullRing },
    { Session::Game::F1_25::Track::MEX_MexicoCity           , Session::Internal::Track::MEX_MexicoCity },
    { Session::Game::F1_25::Track::AZE_Baku                 , Session::Internal::Track::AZE_Baku },
    { Session::Game::F1_25::Track::NED_Zandvoort            , Session::Internal::Track::NED_Zandvoort },
    { Session::Game::F1_25::Track::ITA_Imola                , Session::Internal::Track::ITA_Imola },
    { Session::Game::F1_25::Track::SAU_Jeddah               , Session::Internal::Track::SAU_Jeddah },
    { Session::Game::F1_25::Track::USA_Miami                , Session::Internal::Track::USA_Miami },
    { Session::Game::F1_25::Track::USA_LasVegas             , Session::Internal::Track::USA_LasVegas },
    { Session::Game::F1_25::Track::QAT_Losail               , Session::Internal::Track::QAT_Losail },
};



const std::map<Participant::Game::F1_25::TeamID, Session::Internal::TeamID>
NetCom::Adapter::F1_25::DataConversionMaps::TEAM_ID_MAP = {
    { Participant::Game::F1_25::TeamID::Mercedes        , Session::Internal::TeamID::Mercedes },
    { Participant::Game::F1_25::TeamID::Ferrari         , Session::Internal::TeamID::Ferrari },
    { Participant::Game::F1_25::TeamID::RedBull         , Session::Internal::TeamID::RedBull },
    { Participant::Game::F1_25::TeamID::Williams        , Session::Internal::TeamID::Williams },
    { Participant::Game::F1_25::TeamID::AstonMartin     , Session::Internal::TeamID::AstonMartin },
    { Participant::Game::F1_25::TeamID::Alpine          , Session::Internal::TeamID::Alpine },
    { Participant::Game::F1_25::TeamID::VCARB      , Session::Internal::TeamID::VCARB },
    { Participant::Game::F1_25::TeamID::Haas            , Session::Internal::TeamID::Haas },
    { Participant::Game::F1_25::TeamID::McLaren         , Session::Internal::TeamID::McLaren },
    { Participant::Game::F1_25::TeamID::KickSauber       , Session::Internal::TeamID::KickSauber },
    { Participant::Game::F1_25::TeamID::F1CustomTeam        , Session::Internal::TeamID::Custom },
    { Participant::Game::F1_25::TeamID::APXGP2024        , Session::Internal::TeamID::APXGP },
    { Participant::Game::F1_25::TeamID::APXGP2025        , Session::Internal::TeamID::APXGP },
    { Participant::Game::F1_25::TeamID::Konnersport2024        , Session::Internal::TeamID::Konnersport },
    { Participant::Game::F1_25::TeamID::Konnersport2025        , Session::Internal::TeamID::Konnersport },
    { Participant::Game::F1_25::TeamID::Prema2024           , Session::Internal::TeamID::Prema },
    { Participant::Game::F1_25::TeamID::Virtuosi2024        , Session::Internal::TeamID::Virtuosi },
    { Participant::Game::F1_25::TeamID::Rodin2024          , Session::Internal::TeamID::Rodin },
    { Participant::Game::F1_25::TeamID::AIX2024    , Session::Internal::TeamID::AIX },
    { Participant::Game::F1_25::TeamID::Dams2024            , Session::Internal::TeamID::Dams },
    { Participant::Game::F1_25::TeamID::Campos2024          , Session::Internal::TeamID::Campos },
    { Participant::Game::F1_25::TeamID::VanAmersfoort2024   , Session::Internal::TeamID::VanAmersfoort },
    { Participant::Game::F1_25::TeamID::Trident2024         , Session::Internal::TeamID::Trident },
    { Participant::Game::F1_25::TeamID::Hitech2024          , Session::Internal::TeamID::Hitech },
    { Participant::Game::F1_25::TeamID::Art2024             , Session::Internal::TeamID::Art },
    { Participant::Game::F1_25::TeamID::Hitech2024             , Session::Internal::TeamID::Hitech }

};



const std::map<Participant::Game::F1_25::DriverID, const char*>
NetCom::Adapter::F1_25::DataConversionMaps::DRIVER_SHORTHAND_MAP = {
    { Participant::Game::F1_25::DriverID::NetworkHuman              , "" },     // Deliberately empty
    { Participant::Game::F1_25::DriverID::CarlosSainz               , "SAI" },
    { Participant::Game::F1_25::DriverID::DanielRicciardo           , "RIC" },
    { Participant::Game::F1_25::DriverID::FernandoAlonso            , "ALO" },
    { Participant::Game::F1_25::DriverID::FelipeMassa               , "MAS" },
    { Participant::Game::F1_25::DriverID::LewisHamilton             , "HAM" },
    { Participant::Game::F1_25::DriverID::MaxVerstappen             , "VER" },
    { Participant::Game::F1_25::DriverID::NicoHulkenburg            , "HUL" },
    { Participant::Game::F1_25::DriverID::KevinMagnussen            , "MAG" },
    { Participant::Game::F1_25::DriverID::SergioPerez               , "PER" },
    { Participant::Game::F1_25::DriverID::ValtteriBottas            , "BOT" },
    { Participant::Game::F1_25::DriverID::EstebanOcon               , "OCO" },
    { Participant::Game::F1_25::DriverID::LanceStroll               , "STR" },
    { Participant::Game::F1_25::DriverID::GeorgeRussell             , "RUS" },
    { Participant::Game::F1_25::DriverID::LandoNorris               , "NOR" },
    { Participant::Game::F1_25::DriverID::CharlesLeclerc            , "LEC" },
    { Participant::Game::F1_25::DriverID::PierreGasly               , "GAS" },
    { Participant::Game::F1_25::DriverID::AlexanderAlbon            , "ALB" },
    { Participant::Game::F1_25::DriverID::AyrtonSenna               , "SEB" },
    { Participant::Game::F1_25::DriverID::JuanManuelCorrea          , "COR" },
    { Participant::Game::F1_25::DriverID::MichaelSchumacher         , "MSC" },
    { Participant::Game::F1_25::DriverID::YukiTsunoda               , "TSU" },
    { Participant::Game::F1_25::DriverID::JensonButton              , "BUT" },
    { Participant::Game::F1_25::DriverID::DavidCoulthard            , "COU" },
    { Participant::Game::F1_25::DriverID::OscarPiastri              , "PIA" },
    { Participant::Game::F1_25::DriverID::LiamLawson                , "LAW" },
    { Participant::Game::F1_25::DriverID::RichardVerschoor          , "RVS" },
    { Participant::Game::F1_25::DriverID::EnzoFittipaldi            , "FIT" },
    { Participant::Game::F1_25::DriverID::MarkWebber                , "WEB" },
    { Participant::Game::F1_25::DriverID::JacquesVilleneuve         , "JVI" },
    { Participant::Game::F1_25::DriverID::LoganSargeant             , "SAR" },
    { Participant::Game::F1_25::DriverID::JackDoohan                , "DOO" },
    { Participant::Game::F1_25::DriverID::AmauryCordeel             , "COR" },
    { Participant::Game::F1_25::DriverID::DennisHauger              , "HAU" },
    { Participant::Game::F1_25::DriverID::ZaneMaloney               , "MAL" },
    { Participant::Game::F1_25::DriverID::VictorMartins             , "VMA" },
    { Participant::Game::F1_25::DriverID::OliverBearman             , "BEA" },
    { Participant::Game::F1_25::DriverID::JakCrawford               , "JCA" },
    { Participant::Game::F1_25::DriverID::IsackHadjar               , "HAD" },
    { Participant::Game::F1_25::DriverID::RomanStanek               , "STA" },
    { Participant::Game::F1_25::DriverID::KushMaini                 , "MAI" },
    { Participant::Game::F1_25::DriverID::BrendonLeigh              , "LEI" },
    { Participant::Game::F1_25::DriverID::DavidTonizza              , "TON" },
    { Participant::Game::F1_25::DriverID::JarnoOpmeer               , "OPM" },
    { Participant::Game::F1_25::DriverID::LucasBlakeley             , "LBL" },
    { Participant::Game::F1_25::DriverID::PaulAron                  , "ARO" },
    { Participant::Game::F1_25::DriverID::GabrielBortoleto          , "BOR" },
    { Participant::Game::F1_25::DriverID::FrancoColapinto           , "COL" },
    { Participant::Game::F1_25::DriverID::TaylorBarnard             , "BAR" },
    { Participant::Game::F1_25::DriverID::JoshuaDurksen             , "DUR" },
    { Participant::Game::F1_25::DriverID::AndreaKimiAntonelli       , "ANT" },
    { Participant::Game::F1_25::DriverID::RitomoMiyata              , "MIY" },
    { Participant::Game::F1_25::DriverID::RafaelVillagomez          , "VIL" },
    { Participant::Game::F1_25::DriverID::ZakOSullivan              , "OSU" },
    { Participant::Game::F1_25::DriverID::PepeMarti                 , "MAR" },
    { Participant::Game::F1_25::DriverID::SonnyHayes                , "HAY" },
    { Participant::Game::F1_25::DriverID::JoshuaPierce              , "PIE" },
    { Participant::Game::F1_25::DriverID::CallumVoisin              , "VOI" },
    { Participant::Game::F1_25::DriverID::MatiasZagazeta            , "ZAG" },
    { Participant::Game::F1_25::DriverID::NikolaTsolov              , "TSO" },
    { Participant::Game::F1_25::DriverID::TimTramnitz               , "TRA" },
    { Participant::Game::F1_25::DriverID::LucaCortez                , "COR" }
};