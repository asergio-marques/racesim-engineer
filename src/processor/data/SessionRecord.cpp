#include "data/SessionRecord.h"

#include <cstdint>
#include "data/SessionState.h"
#include "data/internal/Session.h"



Processor::Data::SessionRecord::SessionRecord() :
    m_lastStateTimestamp(0),
    m_type(Session::Internal::Type::InvalidUnknown) {




}



Processor::Data::SessionRecord::~SessionRecord() {




}