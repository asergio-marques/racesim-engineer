#include "data/SessionRecord.h"

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



Processor::Data::SessionRecord::SessionRecord(const uint64_t initTimestamp, const Session::Internal::Settings settings,
    const Session::Internal::TrackInfo trackInfo) :
    m_lastStateTimestamp(initTimestamp),
    m_settings(settings),
    m_trackInfo(trackInfo) {


}



Processor::Data::SessionRecord::~SessionRecord() {



}



const Session::Internal::Settings& Processor::Data::SessionRecord::getSessionSettings() {

    return m_settings;

}


const bool Processor::Data::SessionRecord::Initialized() const {

    const bool sessionLimitSet = (m_settings.m_sessionDurationTime != 0) ||
        (m_settings.m_sessionDurationLaps != 0);

    return (m_trackInfo.m_sessionTrack != Session::Internal::Track::InvalidUnknown) &&
        (m_settings.m_sessionLimit != Session::Internal::LimitType::InvalidUnknown) &&
        sessionLimitSet &&
        (m_settings.m_sessionType != Session::Internal::Type::InvalidUnknown);

}



const Session::Internal::TrackInfo& Processor::Data::SessionRecord::getTrackInfo() {

    return m_trackInfo;

}



Processor::Data::SessionState& Processor::Data::SessionRecord::getModifiableState() {

    return m_state;

}