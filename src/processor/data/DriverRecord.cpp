#include "data/DriverRecord.h"

#include <cstdint>
#include <string>
#include "data/DriverState.h"



Processor::Data::DriverRecord::DriverRecord() :
    m_driverId(0),
    m_driverFullName(""),
    m_lastStateTimestamp(0),
    m_state() {




}



Processor::Data::DriverRecord::~DriverRecord() {




}