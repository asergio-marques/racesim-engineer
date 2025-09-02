#ifndef PROCESSOR_DATA_INCLUDE_DRIVER_INFO_H_
#define PROCESSOR_DATA_INCLUDE_DRIVER_INFO_H_

#include <cstdint>
#include <string>
#include "data/internal/Session.h"



namespace Processor {

    namespace Data {

        struct DriverInfo {

            public:
            // Constructor
            DriverInfo(const Session::Internal::Participant& fullData) :
                m_driverID(fullData.m_index),
                m_isPlayer(fullData.m_isPlayer),
                m_fullName(fullData.m_fullName),
                m_shortName(fullData.m_shortName),
                m_teamID(fullData.m_teamID) {

            }

            // Destructor
            ~DriverInfo() = default;

            // Holds the ID of the driver associated with this record
            const uint8_t m_driverID;

            // Whether the driver to which this data corresponds to is the player
            const bool m_isPlayer;

            // Holds the full-length name of the driver associated with this record
            const std::string m_fullName;

            // Holds the 3-character-length name of the driver associated with this record
            const std::string m_shortName;

            // The ID of the team to which this participant belongs to
            Session::Internal::TeamID m_teamID;

        };

    }

}

#endif //  PROCESSOR_DATA_INCLUDE_DRIVER_INFO_H_