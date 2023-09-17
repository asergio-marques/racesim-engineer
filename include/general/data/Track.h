#ifndef GENERAL_DATA_INCLUDE_F123_TRACK_H_
#define GENERAL_DATA_INCLUDE_F123_TRACK_H_

#include <cstdint>



namespace F1_23 {

    namespace Packet {

        enum class Track : int8_t {

            InvalidUnknown          = -1,
            AUS_Melbourne           = 0,
            FRA_PaulRicard          = 1,
            CHI_Shanghai            = 2,
            BAH_Sakhir              = 3,
            SPA_Catalunya           = 4,
            MON_Monaco              = 5,
            CAN_Montreal            = 6,
            ENG_Silverstone         = 7,
            GER_Hockenheim          = 8,
            HUN_Hungaroring         = 9,
            BEL_Spa                 = 10,
            ITA_Monza               = 11,
            SNG_Singapore           = 12,
            JAP_Suzuka              = 13,
            UAE_AbuDhabi            = 14,
            USA_Texas               = 15,
            BRA_Interlagos          = 16,
            AUS_RedBullRing         = 17,
            RUS_Sochi               = 18,
            MEX_MexicoCity          = 19,
            AZE_Baku                = 20,
            BAH_SakhirShort         = 21,
            ENG_SilverstoneShort    = 22,
            USA_TexasShort          = 23,
            JAP_SuzukaShort         = 24,
            VIE_Hanoi               = 25,
            NED_Zandvoort           = 26,
            ITA_Imola               = 27,
            POR_Portimao            = 28,
            SAU_Jeddah              = 29,
            USA_Miami               = 30,
            USA_LasVegas            = 31,
            QAT_Losail              = 32

        };

    }

}

#endif // GENERAL_DATA_INCLUDE_F123_PACKET_H_