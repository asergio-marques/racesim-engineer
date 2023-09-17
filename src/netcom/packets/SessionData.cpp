#include "netcom/packets/SessionData.h"

#include <cstdint>
#include <iostream>
#include "general/data/Session.h"
#include "general/data/Track.h"
#include "general/data/Player.h"
#include "netcom/packets/IPacket.h"
#include "netcom/packets/Header.h"



F1_23::Packet::SessionData::SessionData() :
    F1_23::Packet::IPacket(),
    m_currentWeather(F1_23::Packet::Weather::InvalidUnknown),
    m_currentTrackTemperature(0),
    m_currentAirTemperature(0),
    m_totalLaps(0),
    m_trackLength(0),
    m_sessionType(F1_23::Packet::SessionType::InvalidUnknown),
    m_trackId(F1_23::Packet::Track::InvalidUnknown),
    m_formula(F1_23::Packet::CarType::InvalidUnknown),
    m_sessionTimeLeft(0),
    m_sessionDuration(0),
    m_pitSpeedLimit(0),
    m_gamePaused(false),
    m_isSpectating(false),
    m_spectatorCarIndex(0),
    m_sliProNativeSupportOn(false),
    m_numMarshalZones(0),
    m_marshalZones(),
    m_safetyCarStatus(F1_23::Packet::SafetyCar::InvalidUnknown),
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
    m_brakingAssist(F1_23::Packet::BrakingAssist::InvalidUnknown),
    m_gearboxAssist(F1_23::Packet::GearboxAssist::InvalidUnknown),
    m_pitAssistOn(false),
    m_pitReleaseAssistOn(false),
    m_ERSAssistOn(false),
    m_DRSAssistOn(false),
    m_dynamicRacingLine(F1_23::Packet::RacingLine::InvalidUnknown),
    m_dynamicRacingLine3D(false),
    m_gameMode(F1_23::Packet::GameMode::InvalidUnknown),
    m_ruleSet(F1_23::Packet::Ruleset::InvalidUnknown),
    m_timeOfDay(0),
    m_sessionLength(F1_23::Packet::SessionLength::InvalidUnknown),
    m_speedUnitPlayer1(F1_23::Packet::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer1(F1_23::Packet::TempUnit::InvalidUnknown),
    m_speedUnitPlayer2(F1_23::Packet::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer2(F1_23::Packet::TempUnit::InvalidUnknown),
    m_numSafetyCarPeriods(0),
    m_numVirtualSafetyCarPeriods(0),
    m_numRedFlagPeriods(0) {

}