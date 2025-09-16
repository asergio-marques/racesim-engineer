#include "data/SessionState.h"

#include <algorithm>
#include "data/SessionRecord.h"
#include "data/internal/Participant.h"
#include "holders/LapInfo.h"



Processor::Data::SessionState::SessionState(Processor::Data::SessionRecord* parent) :
    m_parentRecord(parent),
    m_fastestLap(),
    m_running(true),
    m_weather(),
    m_fastestLap() {




}



Processor::Data::SessionState::~SessionState() {




}



void Processor::Data::SessionState::sessionFinalized() {

    m_running = false;

}



bool Processor::Data::SessionState::Initialized() {

    return m_running && m_weather.Initialized();

}



bool Processor::Data::SessionState::evaluateCompletedLap(const Processor::Data::LapInfo& finishedLap) {

    if (((m_fastestLap.m_lapId == UINT16_MAX) || (finishedLap.m_totalLapTime < m_fastestLap.m_totalLapTime)) &&
        finishedLap.m_isValid && finishedLap.m_totalLapTime.valid()) {

        m_fastestLap = finishedLap;
        return true;

    } else {

        return false;

    }

}



void Processor::Data::SessionState::updateWeather(const Session::Internal::Descriptor& descriptor,
    const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart) {

    m_weather.updateWeather(descriptor, sample, minutesSinceStart);

}



const Processor::Data::WeatherData& Processor::Data::SessionState::weather() const{

    return m_weather;

}


const Processor::Data::LapInfo& Processor::Data::SessionState::fastestLap() const {

    return m_fastestLap;

}