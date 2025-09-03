#include "core/style/Default480p.h"

#include "core/style/480p/Loading.h"
#include "core/style/480p/RaceStanding.h"




UserInterface::Style::Default480p::Default480p() :
    m_loadingStyle(new UserInterface::Style::r480p::Loading),
    m_raceStandingStyle(new UserInterface::Style::r480p::RaceStanding) {



}



UserInterface::Style::ILoading* UserInterface::Style::Default480p::GetLoadingStyle() const {

    return m_loadingStyle;

}



UserInterface::Style::IRaceStanding* UserInterface::Style::Default480p::GetRaceStandingStyle() const {

    return m_raceStandingStyle;

}