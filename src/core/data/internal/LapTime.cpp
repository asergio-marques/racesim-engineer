#include "data/internal/LapTime.h"

#include <cstdint>
#include <string>
#include <stdexcept>



Lap::Internal::Time::Time(const uint32_t milliseconds) :
    m_seconds(milliseconds / 1000),
    m_milliseconds(milliseconds % 1000) {



}



Lap::Internal::Time::Time(const uint8_t seconds, const uint16_t milliseconds) :
    m_seconds(seconds),
    m_milliseconds(milliseconds){



}



Lap::Internal::Time& Lap::Internal::Time::operator=(const Lap::Internal::Time& other) {

    m_milliseconds = other.m_milliseconds;
    m_seconds = other.m_seconds;

    return *this;

}



Lap::Internal::Time& Lap::Internal::Time::operator+=(const Lap::Internal::Time& other) {

    return (*this + other);

}



Lap::Internal::Time& Lap::Internal::Time::operator-=(const Lap::Internal::Time& other) {

    return (*this - other);

}


Lap::Internal::Time Lap::Internal::Time::Time::operator+(const Time& other) {

    const uint16_t msAdd = other.m_milliseconds + m_milliseconds;
    m_seconds += other.m_seconds + (msAdd / 1000);
    m_milliseconds = msAdd % 1000;
    return *this;

}



Lap::Internal::Time Lap::Internal::Time::operator-(const Lap::Internal::Time& other) {

    if (*this >= other) {

        const uint16_t msSub = m_milliseconds + 1000 - other.m_milliseconds;
        m_seconds -= other.m_seconds - (((msSub / 1000) > 0) ? 0 : 1);
        m_milliseconds = msSub % 1000;
    }

    return *this;

}



bool Lap::Internal::Time::operator==(const Time& other) const {

    return (m_seconds == other.m_seconds) && (m_milliseconds == other.m_milliseconds);

}



bool Lap::Internal::Time::operator!=(const Time& other) const {

    return !(*this == other);

}



bool Lap::Internal::Time::operator>(const Time& other) const {

    return (m_seconds > other.m_seconds) ||
        ((m_seconds == other.m_seconds) && (m_milliseconds > other.m_milliseconds));

}



bool Lap::Internal::Time::operator<(const Time& other) const {

    return (m_seconds < other.m_seconds) ||
        ((m_seconds == other.m_seconds) && (m_milliseconds < other.m_milliseconds));

}



bool Lap::Internal::Time::operator>=(const Time& other) const {

    return !(*this < other);

}



bool Lap::Internal::Time::operator<=(const Time& other) const {

    return !(*this > other);

}



void Lap::Internal::Time::zero() {

    m_milliseconds = 0;
    m_seconds = 0;

}



const std::string Lap::Internal::Time::formattedPrint() const {

    return std::to_string(m_seconds) + "." + std::to_string(m_milliseconds);

}



const bool Lap::Internal::Time::valid() const {

    return (m_seconds > 0) && (m_milliseconds > 0) && (m_milliseconds < 1000);

}