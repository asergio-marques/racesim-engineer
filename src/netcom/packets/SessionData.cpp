#include "packets/SessionData.h"

#include <cstdint>
#include <iostream>
#include <math.h>
#include "data/Session.h"
#include "data/Player.h"
#include "packets/IPacket.h"
#include "packets/Header.h"



F1_23::Packet::SessionData::SessionData() :
    F1_23::Packet::IPacket(),
    m_currentWeather(F1_23::Session::Weather::InvalidUnknown),
    m_currentTrackTemperature(0),
    m_currentAirTemperature(0),
    m_totalLaps(0),
    m_trackLength(0),
    m_sessionType(F1_23::Session::Type::InvalidUnknown),
    m_trackId(F1_23::Session::Track::InvalidUnknown),
    m_formula(F1_23::Session::Formula::InvalidUnknown),
    m_sessionTimeLeft(0),
    m_sessionDuration(0),
    m_pitSpeedLimit(0),
    m_gamePaused(false),
    m_isSpectating(false),
    m_spectatorCarIndex(0),
    m_sliProNativeSupportOn(false),
    m_numMarshalZones(0),
    m_marshalZones(),
    m_safetyCarStatus(F1_23::Session::SafetyCar::InvalidUnknown),
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
    m_brakingAssist(F1_23::Player::BrakingAssist::InvalidUnknown),
    m_gearboxAssist(F1_23::Player::GearboxAssist::InvalidUnknown),
    m_pitAssistOn(false),
    m_pitReleaseAssistOn(false),
    m_ERSAssistOn(false),
    m_DRSAssistOn(false),
    m_dynamicRacingLine(F1_23::Player::RacingLine::InvalidUnknown),
    m_dynamicRacingLine3D(false),
    m_gameMode(F1_23::Session::GameMode::InvalidUnknown),
    m_ruleSet(F1_23::Session::Ruleset::InvalidUnknown),
    m_timeOfDay(0),
    m_sessionLength(F1_23::Session::Length::InvalidUnknown),
    m_speedUnitPlayer1(F1_23::Player::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer1(F1_23::Player::TempUnit::InvalidUnknown),
    m_speedUnitPlayer2(F1_23::Player::SpeedUnit::InvalidUnknown),
    m_tempUnitPlayer2(F1_23::Player::TempUnit::InvalidUnknown),
    m_numSafetyCarPeriods(0),
    m_numVirtualSafetyCarPeriods(0),
    m_numRedFlagPeriods(0) {

}