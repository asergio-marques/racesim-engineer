#ifndef USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_
#define USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_

#include <cstdint>



namespace UserInterface {

    namespace Widget {

        enum class StandardImage : uint16_t {

            InvalidUnknown = 0,

            // Backgrounds
            PanelBackgroundLeft = 1,
            PanelBackgroundRight = 2,
            PanelBackgroundFull = 3,

            // Loading
            LoadingLogoCenter = 4,
            LoadingLogoRotatingPart = 5,

            // Driver status
            RetirementBox = 6,

            // Fastest & PB
            FastestLapIcon = 7,
            LapDetailsSessionFastest = 8,
            LapDetailsPersonalBest = 9,

            // Gap details
            LapDetailsInDRSRange = 10,
            LapDetailsDRSActivated = 11,
            LapDetailsGapDecreased = 12,
            LapDetailsGapIncreased = 13,

            // Penalties & warnings
            PenaltyIcon = 14,
            PenaltyTextBackground = 15,
            TrackLimitWarning = 16,
            OtherWarning = 17,

            // Tyre icons
            HardTyres = 18,
            HyperSoftTyres = 19,
            IntermediateTyres = 20,
            MediumTyres = 21,
            SoftTyres = 22,
            SuperSoftTyres = 23,
            WetTyres = 24,
            UnknownTyres = 25,

            // Sector icons
            //// Finished in pits
            FinishedInPitsSectorOf3 = 1003,
            FinishedInPitsSectorOf4 = 1004,
            FinishedInPitsSectorOf5 = 1005,
            FinishedInPitsSectorOf6 = 1006,
            FinishedInPitsSectorOf7 = 1007,
            FinishedInPitsSectorOf8 = 1008,
            FinishedInPitsSectorOf9 = 1009,
            FinishedInPitsSectorOf10 = 1010,
            FinishedInPitsSectorOf11 = 1011,
            FinishedInPitsSectorOf12 = 1012,

            //// Finished invalid
            FinishedInvalidSectorOf3 = 1103,
            FinishedInvalidSectorOf4 = 1104,
            FinishedInvalidSectorOf5 = 1105,
            FinishedInvalidSectorOf6 = 1106,
            FinishedInvalidSectorOf7 = 1107,
            FinishedInvalidSectorOf8 = 1108,
            FinishedInvalidSectorOf9 = 1109,
            FinishedInvalidSectorOf10 = 1110,
            FinishedInvalidSectorOf11 = 1111,
            FinishedInvalidSectorOf12 = 1112,

            //// Finished not improvement
            FinishedNotImprovementSectorOf3 = 1203,
            FinishedNotImprovementSectorOf4 = 1204,
            FinishedNotImprovementSectorOf5 = 1205,
            FinishedNotImprovementSectorOf6 = 1206,
            FinishedNotImprovementSectorOf7 = 1207,
            FinishedNotImprovementSectorOf8 = 1208,
            FinishedNotImprovementSectorOf9 = 1209,
            FinishedNotImprovementSectorOf10 = 1210,
            FinishedNotImprovementSectorOf11 = 1211,
            FinishedNotImprovementSectorOf12 = 1212,

            //// Finished personal best
            FinishedPersonalBestSectorOf3 = 1303,
            FinishedPersonalBestSectorOf4 = 1304,
            FinishedPersonalBestSectorOf5 = 1305,
            FinishedPersonalBestSectorOf6 = 1306,
            FinishedPersonalBestSectorOf7 = 1307,
            FinishedPersonalBestSectorOf8 = 1308,
            FinishedPersonalBestSectorOf9 = 1309,
            FinishedPersonalBestSectorOf10 = 1310,
            FinishedPersonalBestSectorOf11 = 1311,
            FinishedPersonalBestSectorOf12 = 1312,

            //// Finished retirement or complete
            FinishedRetirementCompleteSectorOf3 = 1403,
            FinishedRetirementCompleteSectorOf4 = 1404,
            FinishedRetirementCompleteSectorOf5 = 1405,
            FinishedRetirementCompleteSectorOf6 = 1406,
            FinishedRetirementCompleteSectorOf7 = 1407,
            FinishedRetirementCompleteSectorOf8 = 1408,
            FinishedRetirementCompleteSectorOf9 = 1409,
            FinishedRetirementCompleteSectorOf10 = 1410,
            FinishedRetirementCompleteSectorOf11 = 1411,
            FinishedRetirementCompleteSectorOf12 = 1412,

            //// Finished session fastest
            FinishedSessionFastestSectorOf3 = 1503,
            FinishedSessionFastestSectorOf4 = 1504,
            FinishedSessionFastestSectorOf5 = 1505,
            FinishedSessionFastestSectorOf6 = 1506,
            FinishedSessionFastestSectorOf7 = 1507,
            FinishedSessionFastestSectorOf8 = 1508,
            FinishedSessionFastestSectorOf9 = 1509,
            FinishedSessionFastestSectorOf10 = 1510,
            FinishedSessionFastestSectorOf11 = 1511,
            FinishedSessionFastestSectorOf12 = 1512,

            //// Not run
            NotRunSectorOf3 = 1603,
            NotRunSectorOf4 = 1604,
            NotRunSectorOf5 = 1605,
            NotRunSectorOf6 = 1606,
            NotRunSectorOf7 = 1607,
            NotRunSectorOf8 = 1608,
            NotRunSectorOf9 = 1609,
            NotRunSectorOf10 = 1610,
            NotRunSectorOf11 = 1611,
            NotRunSectorOf12 = 1612,

            //// Running in pits
            RunningInPitsSectorOf3 = 1703,
            RunningInPitsSectorOf4 = 1704,
            RunningInPitsSectorOf5 = 1705,
            RunningInPitsSectorOf6 = 1706,
            RunningInPitsSectorOf7 = 1707,
            RunningInPitsSectorOf8 = 1708,
            RunningInPitsSectorOf9 = 1709,
            RunningInPitsSectorOf10 = 1710,
            RunningInPitsSectorOf11 = 1711,
            RunningInPitsSectorOf12 = 1712,

            //// Running invalid
            RunningInvalidSectorOf3 = 1803,
            RunningInvalidSectorOf4 = 1804,
            RunningInvalidSectorOf5 = 1805,
            RunningInvalidSectorOf6 = 1806,
            RunningInvalidSectorOf7 = 1807,
            RunningInvalidSectorOf8 = 1808,
            RunningInvalidSectorOf9 = 1809,
            RunningInvalidSectorOf10 = 1810,
            RunningInvalidSectorOf11 = 1811,
            RunningInvalidSectorOf12 = 1812,

            //// Running on track
            RunningOnTrackSectorOf3 = 1903,
            RunningOnTrackSectorOf4 = 1904,
            RunningOnTrackSectorOf5 = 1905,
            RunningOnTrackSectorOf6 = 1906,
            RunningOnTrackSectorOf7 = 1907,
            RunningOnTrackSectorOf8 = 1908,
            RunningOnTrackSectorOf9 = 1909,
            RunningOnTrackSectorOf10 = 1910,
            RunningOnTrackSectorOf11 = 1911,
            RunningOnTrackSectorOf12 = 1912,

            // Team icons (should always be the final member)
            //// F1
            TeamIconCustom = 101,
            TeamIconMercedes = 102,
            TeamIconFerrari = 103,
            TeamIconRedBull = 104,
            TeamIconWilliams = 105,
            TeamIconAstonMartin = 106,
            TeamIconAlpine = 107,
            TeamIconAlphaTauri = 108,
            TeamIconHaas = 109,
            TeamIconMcLaren = 110,
            TeamIconAlfaRomeo = 111,
            TeamIconVCARB = 112,
            TeamIconKickSauber = 113,

            // F2
            TeamIconPrema = 200,
            TeamIconVirtuosi = 201,
            TeamIconCarlin = 202,
            TeamIconMPMotorsport = 203,
            TeamIconCharouz = 204,
            TeamIconDams = 205,
            TeamIconCampos = 206,
            TeamIconVanAmersfoort = 207,
            TeamIconTrident = 208,
            TeamIconHitech = 209,
            TeamIconArt = 210,
            TeamIconPHM = 211

        };

    }

}

#endif // USERINTERFACE_WIDGET_INCLUDE_IMAGE_H_