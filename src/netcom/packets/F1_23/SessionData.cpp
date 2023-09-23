#include "packets/F1_23/SessionData.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/F1_23/Session.h"
#include "data/F1_23/Packet.h"
#include "data/F1_23/Player.h"
#include "packets/Helper.h"
#include "packets/F1_23/IPacket.h"
#include "packets/F1_23/Header.h"



Packet::F1_23::SessionData::SessionData(char* packetInfo, Packet::Helper* helper) :
    Packet::F1_23::IPacket(packetInfo),
    m_currentWeather(Session::F1_23::Weather::InvalidUnknown),
    m_currentTrackTemperature(0),
    m_currentAirTemperature(0),
    m_totalLaps(0),
    m_trackLength(0),
    m_sessionType(Session::F1_23::Type::InvalidUnknown),
    m_trackId(Session::F1_23::Track::InvalidUnknown),
    m_formula(Session::F1_23::Formula::InvalidUnknown),
    m_sessionTimeLeft(0),
    m_sessionDuration(0),
    m_pitSpeedLimit(0),
    m_gamePaused(false),
    m_isSpectating(false),
    m_spectatorCarIndex(0),
    m_sliProNativeSupportOn(false),
    m_numMarshalZones(0),
    m_marshalZones(),
    m_safetyCarStatus(Session::F1_23::SafetyCar::InvalidUnknown),
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
    m_brakingAssist(Player::F1_23::BrakingAssist::InvalidUnknown),
    m_gearboxAssist(Player::F1_23::GearboxAssist::InvalidUnknown),
    m_pitAssistOn(false),
    m_pitReleaseAssistOn(false),
    m_ERSAssistOn(false),
    m_DRSAssistOn(false),
    m_dynamicRacingLine(Player::F1_23::RacingLine::InvalidUnknown),
    m_dynamicRacingLine3D(false),
    m_gameMode(Session::F1_23::GameMode::InvalidUnknown),
    m_ruleSet(Session::F1_23::Ruleset::InvalidUnknown),
    m_timeOfDay(0),
    m_sessionLength(Session::F1_23::Length::InvalidUnknown),
    m_speedUnitPlayer1(Player::F1_23::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer1(Player::F1_23::TempUnit::InvalidUnknown),
    m_speedUnitPlayer2(Player::F1_23::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer2(Player::F1_23::TempUnit::InvalidUnknown),
    m_numSafetyCarPeriods(0),
    m_numVirtualSafetyCarPeriods(0),
    m_numRedFlagPeriods(0) {

    if (packetInfo && helper) {

        BuildPacket(packetInfo, helper);

    }
    if (helper) {

        // It is the responsability of the packet class to delete
        // the helper as it is to be used only for this function
        delete helper;

    }

}



const Packet::F1_23::LengthBytes Packet::F1_23::SessionData::GetLength() const {

    return Packet::F1_23::LengthBytes::SessionData;

}



#ifndef NDEBUG
void Packet::F1_23::SessionData::Print() const {

    const Packet::F1_23::Header* header = this->GetHeader();
    if (header) {
        
        header->Print();

    }

    // Packet print TBD

}
#endif // NDEBUG



void Packet::F1_23::SessionData::BuildPacket(char* packetInfo, Packet::Helper* helper) {

    // Start at the end of the header
    size_t arrayStatus = static_cast<size_t>(Packet::F1_23::LengthBytes::Header);
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

}