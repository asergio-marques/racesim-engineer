#include "adapters/F1_25.h"

#include <string>
#include <limits>
#include <vector>
#include "adapters/Interface.h"
#include "data/game/F1_25/Event.h"
#include "data/internal/Participant.h"
#include "data/internal/Session.h"
#include "data/internal/TyreData.h"
#include "maps/F1_25.h"
#include "packets/game/Helper.h"
#include "packets/game/Interface.h"
#include "packets/internal/GridPosition.h"
#include "packets/internal/Interface.h"
#include "packets/internal/LapStatus.h"
#include "packets/internal/ParticipantStatus.h"
#include "packets/internal/PenaltyStatus.h"
#include "packets/internal/SessionParticipants.h"
#include "packets/internal/SessionSettings.h"
#include "packets/internal/Standings.h"
#include "packets/internal/TyreSetUsage.h"
#include "packets/game/F1_25/Interface.h"
#include "packets/game/F1_25/Header.h"
#include "packets/game/F1_25/CarMotionData.h"
#include "packets/game/F1_25/SessionData.h"
#include "packets/game/F1_25/LapData.h"
#include "packets/game/F1_25/EventData.h"
#include "packets/game/F1_25/ParticipantData.h"
#include "packets/game/F1_25/CarSetupData.h"
#include "packets/game/F1_25/CarTelemetryData.h"
#include "packets/game/F1_25/CarStatusData.h"
#include "packets/game/F1_25/StandingsData.h"
#include "packets/game/F1_25/CarDamageData.h"
#include "packets/game/F1_25/SessionHistoryData.h"
#include "packets/game/F1_25/TimeTrialData.h"
#include "packets/game/F1_25/TyreSetData.h"




std::vector<Packet::Internal::Interface*>
Generalizer::Adapter::F1_25::ConvertPacket(const Packet::Game::Interface* packet) {

    if (!packet) {

        return {};

    }

    auto gamePacket = dynamic_cast<const Packet::Game::F1_25::Interface*>(packet);
    if (!gamePacket || !(gamePacket->GetHeader())) {

        return {};

    }

    std::vector<Packet::Internal::Interface*> outputPackets;
    switch (gamePacket->GetHeader()->GetPacketType()) {

        case Packet::Game::F1_25::Type::SessionData:
            outputPackets = ConvertSessionDataPacket(dynamic_cast<const Packet::Game::F1_25::SessionData*>(gamePacket));
            break;

        case Packet::Game::F1_25::Type::LapData:
            outputPackets = ConvertLapDataPacket(dynamic_cast<const Packet::Game::F1_25::LapData*>(gamePacket));
            break;

        case Packet::Game::F1_25::Type::ParticipantData:
            outputPackets = ConvertParticipantDataPacket(dynamic_cast<const Packet::Game::F1_25::ParticipantData*>(gamePacket));
            break;

        case Packet::Game::F1_25::Type::SessionHistoryData:
            outputPackets = ConvertSessionHistoryDataPacket(dynamic_cast<const Packet::Game::F1_25::SessionHistoryData*>(gamePacket));
            break;

        default:
            // do nothing
            break;

    }

    return outputPackets;

}



std::vector<Packet::Internal::Interface*>
Generalizer::Adapter::F1_25::ConvertSessionDataPacket(const Packet::Game::F1_25::SessionData* inputPacket) {

    if (!inputPacket) {

        return {};

    }

    Session::Internal::TrackInfo trackInfo;
    Session::Internal::Settings settings;
    ExtractSessionSettings(inputPacket, trackInfo, settings);
    Packet::Internal::SessionSettings* sessionDataPacket =
        new Packet::Internal::SessionSettings(inputPacket->GetHeader()->GetFrameIdentifier(), trackInfo, settings);

    return { sessionDataPacket };

}



std::vector<Packet::Internal::Interface*>
Generalizer::Adapter::F1_25::ConvertLapDataPacket(const Packet::Game::F1_25::LapData* inputPacket) {

    if (!inputPacket || !(inputPacket->GetHeader())) {

        return {};

    }

    // TODO it doesn't make sense to be creating a gridpacket every time we get a lapdata packet...
    Packet::Internal::GridPosition* gridPacket =
        new Packet::Internal::GridPosition(inputPacket->GetHeader()->GetFrameIdentifier());
    Packet::Internal::Standings* standingsPacket =
        new Packet::Internal::Standings(inputPacket->GetHeader()->GetFrameIdentifier());
    Packet::Internal::PenaltyStatus* penaltiesPacket =
        new Packet::Internal::PenaltyStatus(inputPacket->GetHeader()->GetFrameIdentifier());
    Packet::Internal::ParticipantStatus* statusPacket =
        new Packet::Internal::ParticipantStatus(inputPacket->GetHeader()->GetFrameIdentifier());
    for (size_t i = 0; i < 22; ++i) {

        bool ok = false;
        const auto lapInfo = inputPacket->GetLapInfo(i, ok);
        if (ok) {

            gridPacket->InsertData(i, lapInfo.m_gridPositionStart);
            standingsPacket->InsertData(i, lapInfo.m_carPosition);
            penaltiesPacket->InsertData(i, lapInfo.m_numTotalWarn,
                lapInfo.m_numCornerCutWarn,
                // lap info in seconds, internal packet in milliseconds
                lapInfo.m_timePenalties * 1000,
                lapInfo.m_numUnservedStopGoPens,
                lapInfo.m_numUnservedDTPens);

            // convert status
            Participant::Internal::Status status;
            switch (lapInfo.m_result) {
                case Lap::Game::F1_25::ResultStatus::Active:
                    status = Participant::Internal::Status::Active;
                    break;
                case Lap::Game::F1_25::ResultStatus::Inactive:
                case Lap::Game::F1_25::ResultStatus::NotClassified:
                    status = Participant::Internal::Status::Inactive;
                    break;
                case Lap::Game::F1_25::ResultStatus::DNF:
                case Lap::Game::F1_25::ResultStatus::Retired:
                    status = Participant::Internal::Status::DNF;
                    break;
                case Lap::Game::F1_25::ResultStatus::DSQ:
                    status = Participant::Internal::Status::DSQ;
                    break;
                case Lap::Game::F1_25::ResultStatus::Finished:
                    status = Participant::Internal::Status::FinishedSession;
                    break;
                default:
                    status = Participant::Internal::Status::InvalidUnknown;
            }

            statusPacket->InsertData(i, status);

        }

    }

    return { gridPacket, standingsPacket, penaltiesPacket, statusPacket };

}



std::vector<Packet::Internal::Interface*>
Generalizer::Adapter::F1_25::ConvertParticipantDataPacket(const Packet::Game::F1_25::ParticipantData* inputPacket) {

    if (!inputPacket) {

        return {};

    }

    Packet::Internal::SessionParticipants* participantsPacket =
        new Packet::Internal::SessionParticipants(inputPacket->GetHeader()->GetFrameIdentifier(), inputPacket->GetNumActiveCars());
    auto playerIndex = inputPacket->GetHeader()->GetCarIndexPlayer1();
    for (size_t i = 0; i < inputPacket->GetNumActiveCars(); ++i) {

        bool ok = false;
        const Packet::Game::F1_25::ParticipantInfo rawInfo = inputPacket->GetParticipantInfo(i, ok);
        if (ok) {

            participantsPacket->InsertData(GetSingleParticipantData(rawInfo, i, playerIndex));

        }

    }

    return { participantsPacket };

}


std::vector<Packet::Internal::Interface*>
Generalizer::Adapter::F1_25::ConvertSessionHistoryDataPacket(const Packet::Game::F1_25::SessionHistoryData* inputPacket) {

    if (!inputPacket || !(inputPacket->GetHeader())) {

        return {};

    }

    Packet::Internal::LapStatus* lapPacket =
        new Packet::Internal::LapStatus(inputPacket->GetHeader()->GetFrameIdentifier(), inputPacket->GetCarIndex());

    // Add the previous lap info only if we're not on the first lap
    // Do it before so you guarantee the first member is the previous lap
    if (inputPacket->GetNumLaps() > 1) {
        const auto* previousLapInfo = inputPacket->GetPreviousLapInfo();
        AddLapStatusInfo(inputPacket->GetNumLaps() - 1, previousLapInfo, lapPacket);
    }

    const auto* currentLapInfo = inputPacket->GetCurrentLapInfo();
    AddLapStatusInfo(inputPacket->GetNumLaps(), currentLapInfo, lapPacket);


    Packet::Internal::TyreSetUsage* tyrePacket =
        new Packet::Internal::TyreSetUsage(inputPacket->GetHeader()->GetFrameIdentifier());
    Tyre::Internal::Data tyreData;
    tyreData.m_stintNo = inputPacket->GetNumTyreStints();
    auto stintInfo = inputPacket->GetTyreStintHistoryInfo();
    auto currentLaps = inputPacket->GetNumLaps();

    if (tyreData.m_stintNo == 1) {

        tyreData.m_stintLength = currentLaps;

    }
    else if (tyreData.m_stintNo > 1) {

        tyreData.m_stintLength = currentLaps - inputPacket->GetPreviousStintInfo()->m_endLap;

    }

    auto actualIt = Generalizer::Maps::F1_25::ACTUAL_TYRE_MAP.find(inputPacket->GetCurrentStintInfo()->m_tyreActualCompound);
    if (actualIt != Generalizer::Maps::F1_25::ACTUAL_TYRE_MAP.end()) {

        tyreData.m_actualTyre = actualIt->second;

    }
    auto visualIt = Generalizer::Maps::F1_25::VISUAL_TYRE_MAP.find(inputPacket->GetCurrentStintInfo()->m_tyreVisualCompound);
    if (visualIt != Generalizer::Maps::F1_25::VISUAL_TYRE_MAP.end()) {

        tyreData.m_visualTyre = visualIt->second;

    }

    tyrePacket->InsertData(inputPacket->GetCarIndex(), tyreData);

    return { lapPacket, tyrePacket };

}



void Generalizer::Adapter::F1_25::AddLapStatusInfo(const uint8_t lapNo,
    const Packet::Game::F1_25::LapHistoryInfo* inputInfo,
    Packet::Internal::Interface* outputPacket) const {

    auto castOutputPacket = dynamic_cast<Packet::Internal::LapStatus*>(outputPacket);

    if (inputInfo && castOutputPacket) {

        Packet::Internal::LapStatus::Data lapData;
        lapData.m_lapID = lapNo;
        lapData.m_time = inputInfo->m_lapTime;
        uint32_t sector1TimeMS = (inputInfo->m_sector1TimeMin * 60 * 1000) + inputInfo->m_sector1TimeRemainderMS;
        uint32_t sector2TimeMS = (inputInfo->m_sector2TimeMin * 60 * 1000) + inputInfo->m_sector2TimeRemainderMS;
        uint32_t sector3TimeMS = (inputInfo->m_sector3TimeMin * 60 * 1000) + inputInfo->m_sector3TimeRemainderMS;
        lapData.m_sectorTimes = { sector1TimeMS, sector2TimeMS, sector3TimeMS };
        castOutputPacket->InsertData(lapData);

    }

}




const std::string Generalizer::Adapter::F1_25::ShortenDriverName(const char* originalName) {

    const std::string originalNameStr{ originalName };
    if (originalNameStr.length() == 0) {

        return "";

    }
    else if (originalNameStr.length() <= 3) {

        return originalNameStr;

    }
    else if (originalNameStr == "Player") {

        // clear name if it's default, nothing can be done here
        return "";

    }
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



const Session::Internal::Participant
Generalizer::Adapter::F1_25::GetSingleParticipantData(const Packet::Game::F1_25::ParticipantInfo& rawInfo,
    const uint8_t& arrayIndex,
    const uint8_t& playerIndex) {

    Session::Internal::Participant convertedInfo;
    convertedInfo.m_index = arrayIndex;
    convertedInfo.m_isPlayer = (arrayIndex == playerIndex);

    // This is probably inefficient in cases where the driver is not a "preset" one, but...
    // Attempt to look up the 3-letter version of a predefined game driver
    // If human player, then it will not be found and we'll use the other branch to shorten the username
    // 
    // NOTE: Problems with the shortening method may arise in the case of things like clan tags
    auto driverIt = Generalizer::Maps::F1_25::DRIVER_SHORTHAND_MAP.find(rawInfo.m_driverId);
    if (driverIt != Generalizer::Maps::F1_25::DRIVER_SHORTHAND_MAP.end()) {

        convertedInfo.m_shortName = driverIt->second;

    }
    else {

        convertedInfo.m_shortName = ShortenDriverName(rawInfo.m_name);

    }
    convertedInfo.m_fullName = rawInfo.m_name;

    // Find team to be used as reference in UI
    auto teamIt = Generalizer::Maps::F1_25::TEAM_ID_MAP.find(rawInfo.m_teamId);
    if (teamIt != Generalizer::Maps::F1_25::TEAM_ID_MAP.end()) {

        convertedInfo.m_teamID = teamIt->second;

    }

    return convertedInfo;

}



void Generalizer::Adapter::F1_25::ExtractSessionSettings(const Packet::Game::F1_25::SessionData* inputPacket,
    Session::Internal::TrackInfo& trackInfo,
    Session::Internal::Settings& settings) {

    if (inputPacket) {
        auto it = Generalizer::Maps::F1_25::TRACK_ID_MAP.find(inputPacket->GetTrackId());
        if (it != Generalizer::Maps::F1_25::TRACK_ID_MAP.end()) {

            trackInfo.m_sessionTrack = it->second;

        }
        trackInfo.m_lapDistanceTotal = inputPacket->GetTrackLength();
        trackInfo.m_sector1Distance = inputPacket->GetSector2LapDistanceStart();
        trackInfo.m_sector2Distance = inputPacket->GetSector3LapDistanceStart();
        trackInfo.m_sector3Distance = trackInfo.m_lapDistanceTotal - trackInfo.m_sector1Distance - trackInfo.m_sector2Distance;

        switch (inputPacket->GetSessionType()) {

            case Session::Game::F1_25::Type::FreePractice1:
            case Session::Game::F1_25::Type::FreePractice2:
            case Session::Game::F1_25::Type::FreePractice3:
            case Session::Game::F1_25::Type::ShortPractice:
                settings.m_sessionLimit = Session::Internal::LimitType::TimeElapsed;
                settings.m_sessionType = Session::Internal::Type::FreePractice;
                settings.m_sessionDurationTime = inputPacket->GetSessionDuration();
                break;

            case Session::Game::F1_25::Type::Qualifying1:
            case Session::Game::F1_25::Type::Qualifying2:
            case Session::Game::F1_25::Type::Qualifying3:
            case Session::Game::F1_25::Type::SprintShootout1:
            case Session::Game::F1_25::Type::SprintShootout2:
            case Session::Game::F1_25::Type::SprintShootout3:
            case Session::Game::F1_25::Type::ShortQualifying:
            case Session::Game::F1_25::Type::ShortSprintShootout:
                settings.m_sessionLimit = Session::Internal::LimitType::TimeElapsed;
                settings.m_sessionType = Session::Internal::Type::Qualifying;
                settings.m_sessionDurationTime = inputPacket->GetSessionDuration();
                break;

            case Session::Game::F1_25::Type::OneShotQualifying:
            case Session::Game::F1_25::Type::OneShotSprintShootout:
                settings.m_sessionLimit = Session::Internal::LimitType::LapNumber;
                settings.m_sessionType = Session::Internal::Type::Qualifying;
                settings.m_sessionDurationLaps = 1;
                break;
            case Session::Game::F1_25::Type::TimeTrial:
                break;

            case Session::Game::F1_25::Type::Race1:
            case Session::Game::F1_25::Type::Race2:
            case Session::Game::F1_25::Type::Race3:
                // TODO check if there is a time limit in the F1 game races as well
                settings.m_sessionLimit = Session::Internal::LimitType::LapNumber;
                settings.m_sessionType = Session::Internal::Type::Race;
                settings.m_sessionDurationLaps = inputPacket->GetTotalLaps();
                break;

            default:
                break;

        }

        if (inputPacket->GetFormula() == Session::Game::F1_25::Formula::F2) {

            // TODO check which ones of these are actually used by F2 lmao
            if (inputPacket->GetSessionType() == Session::Game::F1_25::Type::Qualifying1 ||
                inputPacket->GetSessionType() == Session::Game::F1_25::Type::Qualifying2 ||
                inputPacket->GetSessionType() == Session::Game::F1_25::Type::Qualifying3 ||
                inputPacket->GetSessionType() == Session::Game::F1_25::Type::ShortQualifying) {

                settings.m_reverseZone = 10;

            }

        }
        else if (inputPacket->GetSessionType() == Session::Game::F1_25::Type::Qualifying1 ||
         inputPacket->GetSessionType() == Session::Game::F1_25::Type::Qualifying2 ||
         inputPacket->GetSessionType() == Session::Game::F1_25::Type::SprintShootout1 ||
         inputPacket->GetSessionType() == Session::Game::F1_25::Type::SprintShootout2) {

            settings.m_dropZone = 5;

        }

    }

}