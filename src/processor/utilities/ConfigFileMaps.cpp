#include "utilities/ConfigFileMaps.h"

#include <map>
#include <string>
#include "data/internal/Session.h"




const std::vector<Session::Internal::Track>
Processor::Utility::ConfigFileMaps::SUPPORTED_TRACKS = {

    Session::Internal::Track::AUS_Melbourne,
    Session::Internal::Track::AUT_RedBullRing,
    Session::Internal::Track::AZE_Baku,
    Session::Internal::Track::BAH_Sakhir,
    Session::Internal::Track::BEL_Spa,
    Session::Internal::Track::BRA_Interlagos,
    Session::Internal::Track::CAN_Montreal,
    Session::Internal::Track::CHI_Shanghai,
    Session::Internal::Track::ENG_Silverstone,
    Session::Internal::Track::HUN_Hungaroring,
    Session::Internal::Track::ITA_Imola,
    Session::Internal::Track::ITA_Monza,
    Session::Internal::Track::JAP_Suzuka,
    Session::Internal::Track::MEX_MexicoCity,
    Session::Internal::Track::MON_Monaco,
    Session::Internal::Track::NED_Zandvoort,
    Session::Internal::Track::QAT_Losail,
    Session::Internal::Track::SAU_Jeddah,
    Session::Internal::Track::SNG_Singapore,
    Session::Internal::Track::SPA_Catalunya,
    Session::Internal::Track::UAE_AbuDhabi,
    Session::Internal::Track::USA_LasVegas,
    Session::Internal::Track::USA_Miami,
    Session::Internal::Track::USA_Texas,
    Session::Internal::Track::ENG_ReverseSilverstone,
    Session::Internal::Track::AUT_ReverseRedBullRing,
    Session::Internal::Track::NED_ReverseZandvoort

};



const std::map<Session::Internal::Track, std::string>
Processor::Utility::ConfigFileMaps::ID_FILENAME_MAP = {

    { Session::Internal::Track::AUS_Melbourne,              "AlbertPark" },
    { Session::Internal::Track::AUT_RedBullRing,            "RedBullRing" },
    { Session::Internal::Track::AZE_Baku,                   "BakuStreet" },
    { Session::Internal::Track::BAH_Sakhir,                 "Bahrain" },
    { Session::Internal::Track::BEL_Spa,                    "SpaFrancochamps" },
    { Session::Internal::Track::BRA_Interlagos,             "Interlagos" },
    { Session::Internal::Track::CAN_Montreal,               "GillesVilleneuve" },
    { Session::Internal::Track::CHI_Shanghai,               "ShanghaiInternational" },
    { Session::Internal::Track::ENG_Silverstone,            "Silverstone" },
    { Session::Internal::Track::HUN_Hungaroring,            "Hungaroring" },
    { Session::Internal::Track::ITA_Imola,                  "Imola" },
    { Session::Internal::Track::ITA_Monza,                  "Monza" },
    { Session::Internal::Track::JAP_Suzuka,                 "Suzuka" },
    { Session::Internal::Track::MEX_MexicoCity,             "HermanoRodriguez" },
    { Session::Internal::Track::MON_Monaco,                 "Monaco" },
    { Session::Internal::Track::NED_Zandvoort,              "Zandvoort" },
    { Session::Internal::Track::QAT_Losail,                 "LosailInternational" },
    { Session::Internal::Track::SAU_Jeddah,                 "JeddahCorniche" },
    { Session::Internal::Track::SNG_Singapore,              "SingaporeStreet" },
    { Session::Internal::Track::SPA_Catalunya,              "BarcelonaCatalunya" },
    { Session::Internal::Track::UAE_AbuDhabi,               "AbuDhabi" },
    { Session::Internal::Track::USA_LasVegas,               "LasVegasStreet" },
    { Session::Internal::Track::USA_Miami,                  "MiamiStreet" },
    { Session::Internal::Track::USA_Texas,                  "COTA" },
    { Session::Internal::Track::ENG_ReverseSilverstone,     "SilverstoneReverse" },
    { Session::Internal::Track::AUT_ReverseRedBullRing,     "RedBullRingReverse" },
    { Session::Internal::Track::NED_ReverseZandvoort,       "ZandvoortReverse" }

};