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
    m_milliseconds(milliseconds) {



}



Lap::Internal::Time& Lap::Internal::Time::operator=(const Lap::Internal::Time& other) {

    m_milliseconds = other.m_milliseconds;
    m_seconds = other.m_seconds;

    return *this;

}



Lap::Internal::Time& Lap::Internal::Time::operator+=(const Lap::Internal::Time& other) {

    *this = *this + other;
    return *this;

}



Lap::Internal::Time& Lap::Internal::Time::operator-=(const Lap::Internal::Time& other) {

    *this = *this - other;
    return *this;

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



const std::string Lap::Internal::Time::formattedPrint(bool minutes) const {

    std::string minutesString = "";
    std::string secondsString = "";
    std::string millisecondsString = "";
    uint8_t seconds = m_seconds;

    // Prepare minutes if needed
    if (minutes) {
        std::string minutesString = std::to_string(m_seconds / 60);
        seconds = m_seconds % 60;
    }

    // format the string so that there's a leading zero so 2 digits are always displayed
    if (seconds < 10) {
        secondsString = "0" + std::to_string(seconds);
    }
    else {
        secondsString = std::to_string(seconds);
    }

    // format the string so that there's one/two leading zeros so 3 digits are always displayed
    if (m_milliseconds < 10) {
        millisecondsString = "00" + std::to_string(m_milliseconds);
    }
    else if (m_milliseconds < 100) {
        millisecondsString = "0" + std::to_string(m_milliseconds);
    }
    else {
        millisecondsString = std::to_string(m_milliseconds);
    
    }

    // return the appropriate value
    if (minutes) {
        return minutesString + ":" + secondsString + "." + millisecondsString;
    }    
    return secondsString + "." + millisecondsString;

}



const bool Lap::Internal::Time::valid() const {

    return (m_seconds > 0) && (m_milliseconds > 0) && (m_milliseconds < 1000);

}