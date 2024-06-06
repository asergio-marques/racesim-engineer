#include "packets/game/F1_24/SessionData.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/game/F1_24/Session.h"
#include "data/game/F1_24/Packet.h"
#include "data/game/F1_24/Player.h"
#include "packets/game/Helper.h"
#include "packets/game/F1_24/Interface.h"
#include "packets/game/F1_24/Header.h"



Packet::Game::F1_24::SessionData::SessionData(const char* packetInfo, const Packet::Game::F1_24::Header* header, Packet::Game::Helper* helper) :
    Packet::Game::F1_24::Interface(),
    m_currentWeather(Session::Game::F1_24::Weather::InvalidUnknown),
    m_currentTrackTemperature(0),
    m_currentAirTemperature(0),
    m_totalLaps(0),
    m_trackLength(0),
    m_sessionType(Session::Game::F1_24::Type::InvalidUnknown),
    m_trackId(Session::Game::F1_24::Track::InvalidUnknown),
    m_formula(Session::Game::F1_24::Formula::InvalidUnknown),
    m_sessionTimeLeft(0),
    m_sessionDuration(0),
    m_pitSpeedLimit(0),
    m_gamePaused(false),
    m_isSpectating(false),
    m_spectatorCarIndex(0),
    m_sliProNativeSupportOn(false),
    m_numMarshalZones(0),
    m_marshalZones(),
    m_safetyCarStatus(Session::Game::F1_24::SafetyCar::InvalidUnknown),
    m_isNetwork(false),
    m_numWeatherForecastSamples(0),
    m_weatherForecastSamples(),
    m_isForecastApproximate(false),
    m_aiDifficulty(0),
    m_seasonLinkIdentifier(0),
    m_weekendLinkIdentifier(0),
    m_sessionLinkIdentifier(0),
    m_pitStopWindowIdealLap(0),
    m_pitStopWindowLatestLap(0),
    m_pitStopRejoinPosition(0),
    m_steeringAssistOn(false),
    m_brakingAssist(Player::Game::F1_24::BrakingAssist::InvalidUnknown),
    m_gearboxAssist(Player::Game::F1_24::GearboxAssist::InvalidUnknown),
    m_pitAssistOn(false),
    m_pitReleaseAssistOn(false),
    m_ERSAssistOn(false),
    m_DRSAssistOn(false),
    m_dynamicRacingLine(Player::Game::F1_24::RacingLine::InvalidUnknown),
    m_dynamicRacingLine3D(false),
    m_gameMode(Session::Game::F1_24::GameMode::InvalidUnknown),
    m_ruleSet(Session::Game::F1_24::Ruleset::InvalidUnknown),
    m_timeOfDay(0),
    m_sessionLength(Session::Game::F1_24::Length::InvalidUnknown),
    m_speedUnitPlayer1(Player::Game::F1_24::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer1(Player::Game::F1_24::TempUnit::InvalidUnknown),
    m_speedUnitPlayer2(Player::Game::F1_24::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer2(Player::Game::F1_24::TempUnit::InvalidUnknown),
    m_numSafetyCarPeriods(0),
    m_numVirtualSafetyCarPeriods(0),
    m_numRedFlagPeriods(0),
    m_equalCarPerformanceOn(0),
    m_recoveryMode(Session::Game::F1_24::RecoveryMode::InvalidUnknown),
    m_flashbackLimit(Session::Game::F1_24::FlashbackLimit::InvalidUnknown),
    m_surfaceTypeRealistic(0),
    m_lowFuelModeHard(0),
    m_raceStartMode(0),
    m_tyreTemperatureComplex(0),
    m_pitLaneTyreSimOn(0),
    m_carDamage(Session::Game::F1_24::EventRate4State::InvalidUnknown),
    m_carDamageRate(Session::Game::F1_24::EventRate3State::InvalidUnknown),
    m_collisions(Session::Game::F1_24::CollisionSetting::InvalidUnknown),
    m_collisionsOffForFirstLapOnly(0),
    m_mpUnsafePitReleaseOff(0),
    m_mpCollisionOffForGriefing(0),
    m_cornerCuttingStringencyStrict(0),
    m_parcFermeOn(0),
    m_pitStopSetting(Session::Game::F1_24::ExperienceSetting::InvalidUnknown),
    m_safetyCarRate(Session::Game::F1_24::EventRate4State::InvalidUnknown),
    m_safetyCarAIDriven(0),
    m_formationLapOn(0),
    m_formationLapAIDriven(0),
    m_redFlagRate(Session::Game::F1_24::EventRate4State::InvalidUnknown),
    m_affectsLicenceLevelSolo(0),
    m_affectsLicenceLevelMP(0),
    m_numSessionsInWeekend(0),
    m_weekendStructure(),
    m_sector2LapDistanceStart(0),
    m_sector3LapDistanceStart(0) {

    this->SetHeader(header);

    if (packetInfo && helper) {

        helper->SetPacketLength(static_cast<size_t>(this->GetLength()));
        BuildPacket(packetInfo, helper);

    }
    if (helper) {

        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const Packet::Game::F1_24::LengthBytes Packet::Game::F1_24::SessionData::GetLength() const {

    return Packet::Game::F1_24::LengthBytes::SessionData;

}



#ifndef NDEBUG
void Packet::Game::F1_24::SessionData::Print() const {

    const Packet::Game::F1_24::Header* header = this->GetHeader();
    if (header) {
        
        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::Game::F1_24::SessionData::BuildPacket(const char* packetInfo, Packet::Game::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::Game::F1_24::LengthBytes::Header);
    helper->getVariableFromByteStream<>(packetInfo, &m_currentWeather, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_currentTrackTemperature, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_currentAirTemperature, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_totalLaps, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_trackLength, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionType, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_trackId, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_formula, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionTimeLeft, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionDuration, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitSpeedLimit, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_gamePaused, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_isSpectating, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_spectatorCarIndex, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sliProNativeSupportOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numMarshalZones, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_marshalZones, 21, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_safetyCarStatus, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_isNetwork, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numWeatherForecastSamples, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_weatherForecastSamples, 56, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_isForecastApproximate, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_aiDifficulty, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_seasonLinkIdentifier, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_weekendLinkIdentifier, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionLinkIdentifier, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitStopWindowIdealLap, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitStopWindowLatestLap, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitStopRejoinPosition, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_steeringAssistOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_brakingAssist, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_gearboxAssist, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitAssistOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitReleaseAssistOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_ERSAssistOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_DRSAssistOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_dynamicRacingLine, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_dynamicRacingLine3D, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_gameMode, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_ruleSet, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_timeOfDay, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sessionLength, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_speedUnitPlayer1, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_tempUnitPlayer1, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_speedUnitPlayer2, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_tempUnitPlayer2, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numSafetyCarPeriods, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numVirtualSafetyCarPeriods, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numRedFlagPeriods, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_equalCarPerformanceOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_recoveryMode, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_flashbackLimit, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_surfaceTypeRealistic, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_lowFuelModeHard, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_raceStartMode, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_tyreTemperatureComplex, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitLaneTyreSimOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_carDamage, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_carDamageRate, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_collisions, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_collisionsOffForFirstLapOnly, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mpUnsafePitReleaseOff, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_mpCollisionOffForGriefing, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_cornerCuttingStringencyStrict, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_parcFermeOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_pitStopSetting, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_safetyCarRate, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_safetyCarAIDriven, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_formationLapOn, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_formationLapAIDriven, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_redFlagRate, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_affectsLicenceLevelSolo, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_affectsLicenceLevelMP, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_numSessionsInWeekend, arrayStatus);
    helper->getVariableArrayFromByteStream<>(packetInfo, m_weekendStructure, 12, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sector2LapDistanceStart, arrayStatus);
    helper->getVariableFromByteStream<>(packetInfo, &m_sector3LapDistanceStart, arrayStatus);

}