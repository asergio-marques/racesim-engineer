#include "core/style/QuadHD1440p.h"

#include "core/style/1440p/Loading.h"
#include "core/style/1440p/RaceStanding.h"




UserInterface::Style::QuadHD1440p::QuadHD1440p() :
    m_loadingStyle(new UserInterface::Style::r1440p::Loading),
    m_raceStandingStyle(new UserInterface::Style::r1440p::RaceStanding) {



}



UserInterface::Style::ILoading* UserInterface::Style::QuadHD1440p::GetLoadingStyle() const {

    return m_loadingStyle;

}



UserInterface::Style::IRaceStanding* UserInterface::Style::QuadHD1440p::GetRaceStandingStyle() const {

    return m_raceStandingStyle;

}