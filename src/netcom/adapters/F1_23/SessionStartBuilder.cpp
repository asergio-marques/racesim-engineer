#include "adapters/F1_23/SessionStartBuilder.h"

#include <vector>
#include "adapters/F1_23/DataConversionMaps.h"
#include "data/game/F1_23/Session.h"
#include "packets/game/F1_23/Header.h"
#include "packets/game/F1_23/LapData.h"
#include "packets/game/F1_23/ParticipantData.h"
#include "packets/game/F1_23/SessionData.h"
#include "packets/internal/multi_use/SessionStart.h"
#include "packets/internal/tt_types/TimeTrialStart.h"
#include "packets/internal/practice_types/PracticeStart.h"
#include "packets/internal/quali_types/QualiStart.h"
#include "packets/internal/race_types/RaceStart.h"



NetCom::Adapter::F1_23::SessionStartBuilder::SessionStartBuilder() :
    m_enabled(false),
    m_waitingForParticipantData(false),
    m_waitingForSessionData(false),
    m_waitingForLapData(false),
    m_packetBeingBuilt(nullptr) {



}



void NetCom::Adapter::F1_23::SessionStartBuilder::Start() {

    m_enabled = true;
    m_waitingForParticipantData = true;
    m_waitingForSessionData = true;
    m_waitingForLapData = true;

}



void NetCom::Adapter::F1_23::SessionStartBuilder::CreateSessionPacket(const Packet::Game::F1_23::SessionData* gamePacket) {

    if (m_enabled && gamePacket) {

        switch (gamePacket->GetSessionType()) {

            case Session::Game::F1_23::Type::FreePractice1:
            case Session::Game::F1_23::Type::FreePractice2:
            case Session::Game::F1_23::Type::FreePractice3:
            case Session::Game::F1_23::Type::ShortPractice:
                // TODO get more info from packet
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreatePracticeStartPacket(gamePacket);
                break;

            case Session::Game::F1_23::Type::Qualifying1:
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreateQualiStartPacket(gamePacket, 15);
                break;
            case Session::Game::F1_23::Type::Qualifying2:
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreateQualiStartPacket(gamePacket, 10);
                break;
            case Session::Game::F1_23::Type::Qualifying3:
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreateQualiStartPacket(gamePacket, 10);
                break;
            case Session::Game::F1_23::Type::ShortQualifying:
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreateQualiStartPacket(gamePacket, 22);
                break;

            case Session::Game::F1_23::Type::OneShotQualifying:
            case Session::Game::F1_23::Type::TimeTrial:
                // TODO get more info from packet
                // TODO do we need to wait for participant data in this case? Think not
                m_waitingForSessionData = false;
                m_waitingForParticipantData = false;
                m_waitingForLapData = false;
                m_packetBeingBuilt = CreateTimeTrialStartPacket(gamePacket);
                break;

            case Session::Game::F1_23::Type::Race1:
            case Session::Game::F1_23::Type::Race2:
                // TODO get more info from packet
                m_waitingForSessionData = false;
                m_packetBeingBuilt = CreateRaceStartPacket(gamePacket);
                break;

            default:
                break;

        }

    }

}



void NetCom::Adapter::F1_23::SessionStartBuilder::AppendParticipantData(const Packet::Game::F1_23::ParticipantData* gamePacket) {

    if (m_waitingForParticipantData) {

        Packet::Internal::MPSessionStart* packet = dynamic_cast<Packet::Internal::MPSessionStart*>(m_packetBeingBuilt);
        
        // participant data only needed if we're on a non-solo session (anything that isn't TimeTrial)
        if (packet && m_enabled && gamePacket && gamePacket->GetHeader()) {
            // only 1P supported (for now)
            auto playerIndex = gamePacket->GetHeader()->GetCarIndexPlayer1();
            for (uint8_t i = 0; i < gamePacket->GetNumActiveCars(); ++i) {

                bool ok = false;
                const Packet::Game::F1_23::ParticipantInfo rawInfo = gamePacket->GetParticipantInfo(i, ok);
                if (ok) {

                    m_listParticipants.push_back(GetSingleParticipantData(rawInfo, i, playerIndex));

                }

            }

            packet->m_participants = m_listParticipants;
            m_waitingForParticipantData = false;

        }

    }

}

#include <iostream>
void NetCom::Adapter::F1_23::SessionStartBuilder::AppendLapData(const Packet::Game::F1_23::LapData* gamePacket) {

    // Need the indexes from the participant data to add starting positions
    if (m_waitingForLapData && !m_waitingForParticipantData) {

        Packet::Internal::MPSessionStart* packet = dynamic_cast<Packet::Internal::MPSessionStart*>(m_packetBeingBuilt);

        // lap data only needed if we're on a non-solo session (anything that isn't TimeTrial)
        if (packet && m_enabled && gamePacket) {
            
            // check only those we need to check
            for (uint8_t i = 0; i < m_listParticipants.size(); ++i) {

                bool ok = false;
                const Packet::Game::F1_23::LapInfo rawInfo = gamePacket->GetLapInfo(i, ok);
                if (ok) {

                    m_listParticipants[i].m_startPosition = rawInfo.m_gridPositionStart;

                }

            }

            packet->m_participants = m_listParticipants;
            m_waitingForLapData = false;

        }

    }

}



Packet::Internal::SessionStart* NetCom::Adapter::F1_23::SessionStartBuilder::Finish() {

    if (m_enabled && !m_waitingForParticipantData && !m_waitingForSessionData && !m_waitingForLapData) {

        // Temporary holder as the member pointer will be nulled, but the object not deleted
        Packet::Internal::SessionStart* ret = m_packetBeingBuilt;

        // Revert the builder status to default
        m_packetBeingBuilt = nullptr;
        m_enabled = false;
        m_listParticipants.clear();

        return ret;

    }

    return nullptr;

}



Packet::Internal::TimeTrialStart*
    NetCom::Adapter::F1_23::SessionStartBuilder::CreateTimeTrialStartPacket(const Packet::Game::F1_23::SessionData* gamePacket) {

    Packet::Internal::TimeTrialStart* newTTPacket = new Packet::Internal::TimeTrialStart(gamePacket->GetHeader()->GetFrameIdentifier());
    ConvertTrackID(newTTPacket, gamePacket);
    return newTTPacket;

}



Packet::Internal::PracticeStart*
    NetCom::Adapter::F1_23::SessionStartBuilder::CreatePracticeStartPacket(const Packet::Game::F1_23::SessionData* gamePacket) {

    Packet::Internal::PracticeStart* newPracticePacket = new Packet::Internal::PracticeStart(gamePacket->GetHeader()->GetFrameIdentifier());
    ConvertTrackID(newPracticePacket, gamePacket);
    if (!m_listParticipants.empty()) {

        newPracticePacket->m_participants = m_listParticipants;

    }
    return newPracticePacket;

}



Packet::Internal::QualiStart*
    NetCom::Adapter::F1_23::SessionStartBuilder::CreateQualiStartPacket(const Packet::Game::F1_23::SessionData* gamePacket, uint8_t numClassifiedAtEnd) {

    Packet::Internal::QualiStart* newQualiPacket = new Packet::Internal::QualiStart(gamePacket->GetHeader()->GetFrameIdentifier(), numClassifiedAtEnd);
    ConvertTrackID(newQualiPacket, gamePacket);
    if (!m_listParticipants.empty()) {

        newQualiPacket->m_participants = m_listParticipants;

    }
    return newQualiPacket;

}



Packet::Internal::RaceStart*
    NetCom::Adapter::F1_23::SessionStartBuilder::CreateRaceStartPacket(const Packet::Game::F1_23::SessionData* gamePacket) {

    Packet::Internal::RaceStart* newRacePacket = new Packet::Internal::RaceStart(gamePacket->GetHeader()->GetFrameIdentifier(), gamePacket->GetTotalLaps());
    ConvertTrackID(newRacePacket, gamePacket);
    if (!m_listParticipants.empty()) {

        newRacePacket->m_participants = m_listParticipants;

    }
    return newRacePacket;

}



void NetCom::Adapter::F1_23::SessionStartBuilder::ConvertTrackID(Packet::Internal::SessionStart* newPacket,
    const Packet::Game::F1_23::SessionData* gamePacket) {

    if (newPacket && gamePacket) {
        auto it = NetCom::Adapter::F1_23::DataConversionMaps::TRACK_ID_MAP.find(gamePacket->GetTrackId());
        if (it != NetCom::Adapter::F1_23::DataConversionMaps::TRACK_ID_MAP.end()) {

            newPacket->m_sessionTrack = it->second;

        }
        // no need for else; default is already "Unknown" track

    }

}



const std::string NetCom::Adapter::F1_23::SessionStartBuilder::ShortenDriverName(const char* originalName) {

    const std::string originalNameStr{ originalName };
    if (originalNameStr.length() == 0) {
        
        return "???";

    }
    else if (originalNameStr.length() <= 3) {
        
        return originalNameStr;

    }
    else {

        // Use only the first 3 consonants
        std::string shortName = "";
        for (const char character : originalNameStr) {

            // holy hell this is damn ugly
            if (character != 'A' &&
                character != 'E' &&
                character != 'I' &&
                character != 'O' &&
                character != 'U') {

                shortName.push_back(character);
                if (shortName.length() == 3) {
                    break;
                }

            }

        }
        return shortName;

    }

}

const Session::Internal::Participant
NetCom::Adapter::F1_23::SessionStartBuilder::GetSingleParticipantData(const Packet::Game::F1_23::ParticipantInfo& rawInfo,
    const uint8_t& arrayIndex,
    const uint8_t& playerIndex) {

    Session::Internal::Participant convertedInfo;
    convertedInfo.m_index = arrayIndex;
    convertedInfo.m_isPlayer = (arrayIndex == playerIndex);
    
    // This is probably inefficient in cases where the driver is not a "preset" one, but...
    // Attempt to look up the 3-letter version of a predefined game driver, if human player,
    // Then the string will be empty and the game will be forced to "shorten" the username
    // 
    // NOTE: Problems with the shortening method may arise in the case of things like clan tags
    auto driverIt = NetCom::Adapter::F1_23::DataConversionMaps::DRIVER_SHORTHAND_MAP.find(rawInfo.m_driverId);
    if (driverIt != NetCom::Adapter::F1_23::DataConversionMaps::DRIVER_SHORTHAND_MAP.end() &&
        std::strcmp(driverIt->second, "")) {
        convertedInfo.m_shortName = ShortenDriverName(driverIt->second);
    }
    else {
        convertedInfo.m_shortName = ShortenDriverName(rawInfo.m_name);
    }
    convertedInfo.m_fullName = rawInfo.m_name;

    // Find team to be used as reference in UI
    auto teamIt = NetCom::Adapter::F1_23::DataConversionMaps::TEAM_ID_MAP.find(rawInfo.m_teamId);
    if (teamIt != NetCom::Adapter::F1_23::DataConversionMaps::TEAM_ID_MAP.end()) {

        convertedInfo.m_TeamIcon = teamIt->second;

    }

    return convertedInfo;

}