#include "data/internal/TyreData.h"

#include <cstdint>
#include "data/internal/Tyre.h"



Tyre::Internal::Data::Data() :
    m_hasID(false),
    m_setID(UINT8_MAX),
    m_actualTyre(Tyre::Internal::Actual::InvalidUnknown),
    m_visualTyre(Tyre::Internal::Visual::InvalidUnknown),
    m_hasAge(false),
    m_ageLaps(UINT8_MAX) {


}




Tyre::Internal::Data& Tyre::Internal::Data::operator=(const Data& other) {

    m_hasID = other.m_hasID;
    m_setID = other.m_setID;
    m_actualTyre = other.m_actualTyre;
    m_visualTyre = other.m_visualTyre;
    m_hasAge = other.m_hasAge;
    m_ageLaps = other.m_ageLaps;

    return *this;

}



bool Tyre::Internal::Data::operator==(const Tyre::Internal::Data& other) {

    return (m_hasID == other.m_hasID) &&
        (m_setID == other.m_setID) &&
        (m_actualTyre == other.m_actualTyre) &&
        (m_visualTyre == other.m_visualTyre) &&
        (m_hasAge == other.m_hasAge) &&
        (m_ageLaps == other.m_ageLaps);

}



bool Tyre::Internal::Data::operator!=(const Tyre::Internal::Data& other) {

    return (*this == other);

}