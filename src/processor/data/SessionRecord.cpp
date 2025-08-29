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



const Session::Internal::TrackInfo& Processor::Data::SessionRecord::getTrackInfo() {

    return m_trackInfo;

}



Processor::Data::SessionState& Processor::Data::SessionRecord::getModifiableState() {

    return m_state;

}