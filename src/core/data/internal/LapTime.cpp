#include "data/internal/LapTime.h"

#include <cstdint>
#include <cassert>
#include <string>
#include <stdexcept>



Lap::Internal::Time::Time(const uint32_t milliseconds) :
    m_seconds(milliseconds / 1000),
    m_milliseconds(milliseconds % 1000) {



}



Lap::Internal::Time::Time(const uint32_t seconds, const uint16_t milliseconds) :
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

    if (*this > other) {

        const uint32_t diffTimeMs = ((m_seconds * 1000) + m_milliseconds) - ((other.m_seconds) * 1000 + other.m_milliseconds);
        return Lap::Internal::Time{ diffTimeMs };

    }

    return Lap::Internal::Time{ 0 };

}


Lap::Internal::Time Lap::Internal::Time::operator*(const float_t& coef) {

    uint32_t totalMs = (m_seconds * 1000) + m_milliseconds;
    totalMs *= coef;
    m_seconds = totalMs / 1000;
    m_milliseconds = totalMs % 1000;
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



const std::string Lap::Internal::Time::formattedPrint(bool useMinutes) const {

    std::string minutesString = "";
    std::string secondsString = "";
    std::string millisecondsString = "";
    uint32_t seconds = m_seconds;
    uint32_t minutes = m_seconds / 60;

    // Prepare minutes if needed
    if (useMinutes) {
        minutesString = std::to_string(minutes);
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
    if (useMinutes && minutes > 0) {
        return minutesString + ":" + secondsString + "." + millisecondsString;
    }
    return secondsString + "." + millisecondsString;

}



const bool Lap::Internal::Time::valid() const {

    return (m_seconds > 0) && (m_milliseconds > 0) && (m_milliseconds < 1000);

}