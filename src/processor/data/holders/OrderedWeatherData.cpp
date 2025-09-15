#include "data/holders/OrderedWeatherData.h"

#include <cstdint>
#include "data/internal/Session.h"




Processor::Data::OrderedWeatherData::OrderedWeatherData(const uint16_t minutesSinceStart, const uint16_t m_timeOffset) : 
    m_minutesSinceStart(minutesSinceStart + m_timeOffset),
    m_sample() {



}



Processor::Data::OrderedWeatherData& Processor::Data::OrderedWeatherData::operator=(const Processor::Data::OrderedWeatherData& other) {

    m_sample = other.m_sample;
    return *this;

}



bool Processor::Data::OrderedWeatherData::operator==(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart == other.m_minutesSinceStart);

}



bool Processor::Data::OrderedWeatherData::operator!=(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart != other.m_minutesSinceStart);

}



bool Processor::Data::OrderedWeatherData::operator>(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart > other.m_minutesSinceStart);

}



bool Processor::Data::OrderedWeatherData::operator<(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart < other.m_minutesSinceStart);

}



bool Processor::Data::OrderedWeatherData::operator>=(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart >= other.m_minutesSinceStart);

}



bool Processor::Data::OrderedWeatherData::operator<=(const Processor::Data::OrderedWeatherData& other) const {

    return (m_minutesSinceStart <= other.m_minutesSinceStart);

}