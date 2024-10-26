#include "data/SessionRecord.h"

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



Processor::Data::SessionRecord::SessionRecord(const uint64_t initTimestamp, const Session::Internal::Type sessionType, const Session::Internal::Track trackID, const uint8_t numLaps) :
    m_lastStateTimestamp(initTimestamp),
    m_type(sessionType),
    m_trackID(trackID),
    m_totalLaps(numLaps) {


}



Processor::Data::SessionRecord::~SessionRecord() {




}



Processor::Data::SessionState& Processor::Data::SessionRecord::getModifiableState() {

    return m_state;

}