#include "core/style/UltraHD4K.h"

#include "core/style/4K/Loading.h"
#include "core/style/4K/RaceStanding.h"




UserInterface::Style::UltraHD4K::UltraHD4K() :
    m_loadingStyle(new UserInterface::Style::r4K::Loading),
    m_raceStandingStyle(new UserInterface::Style::r4K::RaceStanding) {



}



UserInterface::Style::ILoading* UserInterface::Style::UltraHD4K::GetLoadingStyle() const {

    return m_loadingStyle;

}



UserInterface::Style::IRaceStanding* UserInterface::Style::UltraHD4K::GetRaceStandingStyle() const {

    return m_raceStandingStyle;

}