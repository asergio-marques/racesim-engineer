#include "data/internal/TyreData.h"

#include <cstdint>
#include "data/internal/Tyre.h"



Tyre::Internal::Data::Data() :
    m_stintNo(UINT8_MAX),
    m_stintLength(UINT8_MAX),
    m_actualTyre(Tyre::Internal::Actual::InvalidUnknown),
    m_visualTyre(Tyre::Internal::Visual::InvalidUnknown) {


}




Tyre::Internal::Data& Tyre::Internal::Data::operator=(const Data& other) {

    m_stintNo = other.m_stintNo;
    m_stintLength = other.m_stintLength;
    m_actualTyre = other.m_actualTyre;
    m_visualTyre = other.m_visualTyre;

    return *this;

}



bool Tyre::Internal::Data::operator==(const Tyre::Internal::Data& other) {

    return (m_stintNo == other.m_stintNo) &&
        (m_stintLength == other.m_stintLength) &&
        (m_actualTyre == other.m_actualTyre) &&
        (m_visualTyre == other.m_visualTyre);

}



bool Tyre::Internal::Data::operator!=(const Tyre::Internal::Data& other) {

    return (*this == other);

}