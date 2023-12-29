#ifndef DATA_INTERNAL_INCLUDE_SESSION_H_
#define DATA_INTERNAL_INCLUDE_SESSION_H_

#include <cstdint>
#include <string>



namespace Session::Internal {

    enum class Type : uint8_t {

        InvalidUnknown = 0,
        TimeTrial = 1,
        FreePractice = 2,
        Qualifying = 3,
        Race = 4

    };

    enum class TeamID : uint8_t {

        // F1 teams 2021+
        Mercedes = 0,
        Ferrari = 1,
        RedBull = 2,
        Williams = 3,
        AstonMartin = 4,
        Alpine = 5,
        AlphaTauri = 6,
        Haas = 7,
        McLaren = 8,
        AlfaRomeo = 9,

        // F2 teams 2022+
        Prema = 10,
        Virtuosi = 11,
        Carlin = 12,
        MPMotorsport = 13,
        Charouz = 14,
        Dams = 15,
        Campos = 16,
        VanAmersfoort = 17,
        Trident = 18,
        Hitech = 19,
        Art = 20

    };

    struct Participant {

        // Whether the current participant is the player
        bool m_isPlayer;

        // Index for this participant
        uint8_t m_index;

        // 3-letter name for display
        std::string m_shortName;

        // Which team icon ought be displayed
        Session::Internal::TeamID m_TeamIcon;

    };

}

#endif // DATA_INTERNAL_INCLUDE_SESSION_H_