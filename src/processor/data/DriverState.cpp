#include "data/DriverState.h"

#include <cstdint>
#include <vector>



Processor::Data::DriverState::DriverState(const uint8_t startingPosition) :
    m_startingPosition(startingPosition),
    m_currentPosition(startingPosition) {




}



Processor::Data::DriverState::~DriverState() {




}




const std::vector<Processor::Data::DriverState::Comparison>
    Processor::Data::DriverState::CompareState(const Processor::Data::DriverState& other) {

    std::vector<Processor::Data::DriverState::Comparison> differenceList;
    if (other.m_currentPosition != m_currentPosition) differenceList.push_back(Processor::Data::DriverState::Comparison::PositionChange);

    return differenceList;
}