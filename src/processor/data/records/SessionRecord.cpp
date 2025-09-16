#include "data/SessionRecord.h"

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



Processor::Data::SessionRecord::SessionRecord(const uint64_t initTimestamp, const Session::Internal::Settings settings,
    const Processor::Data::TrackData& detailedTrackData) :
    m_lastStateTimestamp(initTimestamp),
    m_settings(settings),
    m_track(detailedTrackData),
    m_state(new Processor::Data::SessionState(this))  {

}



Processor::Data::SessionRecord::~SessionRecord() {

    if (m_state) {
    
        delete m_state;

    }
    m_state = nullptr;

}


const bool Processor::Data::SessionRecord::Initialized() const {

    const bool sessionLimitSet = (m_settings.m_sessionDurationTime != 0) ||
        (m_settings.m_sessionDurationLaps != 0);

    return (m_trackInfo.m_sessionTrack != Session::Internal::Track::InvalidUnknown) &&
        (m_settings.m_sessionLimit != Session::Internal::LimitType::InvalidUnknown) &&
        sessionLimitSet &&
        (m_settings.m_sessionType != Session::Internal::Type::InvalidUnknown) &&
        m_state && m_state->Initialized();

}



void Processor::Data::SessionRecord::updateWeather(const Session::Internal::Descriptor& descriptor,
    const Session::Internal::WeatherSample& sample, const uint16_t minutesSinceStart) {

    m_state.updateWeather(descriptor, sample, minutesSinceStart);
    // update the current state for accuracy
    if (m_state && (sample.m_timeOffset == 0)) {

        // TODO implement this
        // m_state->updateCurrentWeather(descriptor, sample, minutesSinceStart);

    }

}



const Session::Internal::TrackData& Processor::Data::SessionRecord::getTrackData() {

    return m_track;

}



const Session::Internal::Settings& Processor::Data::SessionRecord::getSessionSettings() {

    return m_settings;

}



Processor::Data::SessionState* Processor::Data::SessionRecord::getModifiableState() {

    return m_state;

}



void Processor::Data::SessionRecord::PrintWeather(const Session::Internal::Descriptor& descriptor) {

    m_state->weather().Print(descriptor);

}