#ifndef DATA_GAME_F123_INCLUDE_PARTICIPANT_H_
#define DATA_GAME_F123_INCLUDE_PARTICIPANT_H_

#include <cstdint>



namespace Participant::Game::F1_23 {

    enum class TeamID : uint8_t {

        Mercedes2023                    = 0,
        Ferrari2023                     = 1,
        RedBull2023                     = 2,
        Williams2023                    = 3,
        AstonMartin2023                 = 4,
        Alpine2023                      = 5,
        AlphaTauri2023                  = 6,
        Haas2023                        = 7,
        McLaren2023                     = 8,
        AlfaRomeo2023                   = 9,
        Mercedes2020                    = 85,
        Ferrari2020                     = 86,
        RedBull2020                     = 87,
        Williams2020                    = 88,
        RacingPoint2020                 = 89,
        Renault2020                     = 90,
        AlphaTauri2020                  = 91,
        Haas2020                        = 92,
        McLaren2020                     = 93,
        AlfaRomeo2020                   = 94,
        AstonMartinDB11V12              = 95,
        AstonMartinVantageF1Edition     = 96,
        AstonMartinVantageSafetyCar     = 97,
        FerrariF8Tributo                = 98,
        FerrariRoma                     = 99,
        McLaren720S                     = 100,
        McLarenArtura                   = 101,
        MercedesAMGGTBlackSafetyCar     = 102,
        MercedesAMGGTRPro               = 103,
        F1CustomTeam                    = 104,
        Prema2021                       = 106,
        UniVirtuosi2021                 = 107,
        Carlin2021                      = 108,
        Hitech2021                      = 109,
        Art2021                         = 110,
        MPMotorsport2021                = 111,
        Charouz2021                     = 112,
        Dams2021                        = 113,
        Campos2021                      = 114,
        BWT2021                         = 115,
        Trident2021                     = 116,
        MercedesAMGGTBlack              = 117,
        Mercedes2022                    = 118,
        Ferrari2022                     = 119,
        RedBull2022                     = 120,
        Williams2022                    = 121,
        AstonMartin2022                 = 122,
        Alpine2022                      = 123,
        AlphaTauri2022                  = 124,
        Haas2022                        = 125,
        McLaren2022                     = 126,
        AlfaRomeo2022                   = 127,
        Konnersport2022                 = 128,
        Konnersport                     = 129,
        Prema2022                       = 130,
        Virtuosi2022                    = 131,
        Carlin2022                      = 132,
        MPMotorsport2022                = 133,
        Charouz2022                     = 134,
        Dams2022                        = 135,
        Campos2022                      = 136,
        VanAmersfoort2022               = 137,
        Trident2022                     = 138,
        Hitech2022                      = 139,
        Art2022                         = 140

    };

    enum class DriverID : uint8_t {

        CarlosSainz             = 0,
        DaniilKvyat             = 1,
        DanielRicciardo         = 2,
        FernandoAlonso          = 3,
        FelipeMassa             = 4,
        KimiRaikkonen           = 6,
        LewisHamilton           = 7,
        MaxVerstappen           = 9,
        NicoHulkenburg          = 10,
        KevinMagnussen          = 11,
        RomainGrosjean          = 12,
        SebastianVettel         = 13,
        SergioPerez             = 14,
        ValtteriBottas          = 15,
        EstebanOcon             = 17,
        LanceStroll             = 19,
        ArronBarnes             = 20,
        MartinGiles             = 21,
        AlexMurray              = 22,
        LucasRoth               = 23,
        IgorCorreia             = 24,
        SophieLevasseur         = 25,
        JonasSchiffer           = 26,
        AlainForest             = 27,
        JayLetourneau           = 28,
        EstoSaari               = 29,
        YasarAtiyeh             = 30,
        CallistoCalabresi       = 31,
        NaotaIzum               = 32,
        HowardClarke            = 33,
        WilheimKaufmann         = 34,
        MarieLaursen            = 35,
        FlavioNieves            = 36,
        PeterBelousov           = 37,
        KlimekMichalski         = 38,
        SantiagoMoreno          = 39,
        BenjaminCoppens         = 40,
        NoahVisser              = 41,
        GertWaldmuller          = 42,
        JulianQuesada           = 43,
        DanielJones             = 44,
        ArtemMarkelov           = 45,
        TadasukeMakino          = 46,
        SeanGelael              = 47,
        NyckDeVries             = 48,
        JackAitken              = 49,
        GeorgeRussell           = 50,
        MaximilianGunther       = 51,
        NireiFukuzumi           = 52,
        LucaGhiotto             = 53,
        LandoNorris             = 54,
        SergioSetteCamara       = 55,
        LouisDeletraz           = 56,
        AntonioFuoco            = 57,
        CharlesLeclerc          = 58,
        PierreGasly             = 59,
        AlexanderAlbon          = 62,
        NicholasLatifi          = 63,
        DorianBoccolacci        = 64,
        NikoKari                = 65,
        RobertoMerhi            = 66,
        ArjunMaini              = 67,
        AlessioLorandi          = 68,
        RubenMeijer             = 69,
        RashidNair              = 70,
        JackTremblay            = 71,
        DevonButler             = 72,
        LukasWeber              = 73,
        AntonioGiovinazzi       = 74,
        RobertKubica            = 75,
        AlainProst              = 76,
        AyrtonSenna             = 77,
        NobuharuMatsushita      = 78,
        NikitaMazepin           = 79,
        GuanyaZhou              = 80,
        MickSchumacher          = 81,
        CallumIlott             = 82,
        JuanManuelCorrea        = 83,
        JordanKing              = 84,
        MahaveerRaghunathan     = 85,
        TatianaCalderon         = 86,
        AnthoineHubert          = 87,
        GuilianoAlesi           = 88,
        RalphBoschung           = 89,
        MichaelSchumacher       = 90,
        DanTicktum              = 91,
        MarcusArmstrong         = 92,
        ChristianLundgaard      = 93,
        YukiTsunoda             = 94,
        JehanDaruvala           = 95,
        GulhermeSamaia          = 96,
        PedroPiquet             = 97,
        FelipeDrugovich         = 98,
        RobertSchwartzman       = 99,
        RoyNissany              = 100,
        MarinoSato              = 101,
        AidanJackson            = 102,
        CasperAkkerman          = 103,
        JensonButton            = 109,
        DavidCoulthard          = 110,
        NicoRosberg             = 111,
        OscarPiastri            = 112,
        LiamLawson              = 113,
        JuriVips                = 114,
        TheoPourchaire          = 115,
        RichardVerschoor        = 116,
        LirimZendeli            = 117,
        DavidBeckmann           = 118,
        AlessioDeledda          = 121,
        BentViscaal             = 122,
        EnzoFittipaldi          = 123,
        MarkWebber              = 125,
        JacquesVilleneuve       = 126,
        CallieMayer             = 127,
        NoahBell                = 128,
        JakeHughes              = 129,
        FrederikVesti           = 130,
        OlliCaldwell            = 131,
        LoganSargeant           = 132,
        CemBolukbasi            = 133,
        AyumuIwasa              = 134,
        ClementNovalak          = 135,
        JackDoohan              = 136,
        AmauryCordeel           = 137,
        DennisHauger            = 138,
        CalanWilliams           = 139,
        JamieChadwick           = 140,
        KamuiKobayashi          = 141,
        PastorMaldonado         = 142,
        MikaHakkinen            = 143,
        NigelMansell            = 144,
        NetworkHuman            = 255

    };

    enum class Nationality : uint8_t {

        USA                 = 1,
        Argentina           = 2,
        Australia           = 3,
        Austria             = 4,
        Azerbaijan          = 5,
        Bahrain             = 6,
        Belgium             = 7,
        Bolivia             = 8,
        Brazil              = 9,
        GreatBritain        = 10,
        Bulgaria            = 11,
        Cameroon            = 12,
        Canada              = 13,
        Chile               = 14,
        China               = 15,
        Colombia            = 16,
        CostaRica           = 17,
        Croatia             = 18,
        Cyprus              = 19,
        Czechia             = 20,
        Denmark             = 21,
        Netherlands         = 22,
        Ecuador             = 23,
        England             = 24,
        UAE                 = 25,
        Estonia             = 26,
        Finland             = 27,
        France              = 28,
        Germany             = 29,
        Ghana               = 30,
        Greece              = 31,
        Guatemala           = 32,
        Honduras            = 33,
        HongKong            = 34,
        Hungary             = 35,
        Iceland             = 36,
        India               = 37,
        Indonesia           = 38,
        Ireland             = 39,
        Israel              = 40,
        Italy               = 41,
        Jamaica             = 42,
        Japan               = 43,
        Jordan              = 44,
        Kuwait              = 45,
        Latvia              = 46,
        Lebanon             = 47,
        Lithuania           = 48,
        Luxembourg          = 49,
        Malaysia            = 50,
        Malta               = 51,
        Mexico              = 52,
        Monaco              = 53,
        NewZealand          = 54,
        Nicaragua           = 55,
        NorthernIreland     = 56,
        Norway              = 57,
        Oman                = 58,
        Pakistan            = 59,
        Panama              = 60,
        Paraguay            = 61,
        Peru                = 62,
        Poland              = 63,
        Portugal            = 64,
        Qatar               = 65,
        Romania             = 66,
        Russia              = 67,
        ElSalvador          = 68,
        SaudiArabia         = 69,
        Scotland            = 70,
        Serbia              = 71,
        Singapore           = 72,
        Slovakia            = 73,
        Slovenia            = 74,
        SouthKorea          = 75,
        SouthAfrica         = 76,
        Spain               = 77,
        Sweden              = 78,
        Switzerland         = 79,
        Thailand            = 80,
        Turkey              = 81,
        Uruguay             = 82,
        Ukraine             = 83,
        Venezuela           = 84,
        Barbados            = 85,
        Wales               = 86,
        Vietnam             = 87,
        NetworkHuman        = 255

    };

}

#endif // DATA_GAME_F123_INCLUDE_PARTICIPANT_H_