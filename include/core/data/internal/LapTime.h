#ifndef DATA_INTERNAL_INCLUDE_LAP_TIME_H_
#define DATA_INTERNAL_INCLUDE_LAP_TIME_H_

#include <cstdint>
#include <string>



namespace Lap::Internal {

    struct Time {

        Time() = default;
        Time(const uint32_t milliseconds);
        Time(const uint8_t seconds, const uint16_t milliseconds);
        Time(const Time& other) = default;
        Time& operator=(const Time& other);
        Time& operator+=(const Time& other);
        Time& operator-=(const Time& other);
        Time operator+(const Time& other);
        Time operator-(const Time& other);
        bool operator==(const Time& other) const;
        bool operator!=(const Time& other) const;
        bool operator>(const Time& other) const;
        bool operator<(const Time& other) const;
        bool operator>=(const Time& other) const;
        bool operator<=(const Time& other) const;
        void zero();
        const std::string formattedPrint(bool minutes = false) const;
        const bool valid() const;

        uint8_t m_seconds;
        uint16_t m_milliseconds;

    };

}



#endif // DATA_INTERNAL_INCLUDE_LAP_TIME_H_