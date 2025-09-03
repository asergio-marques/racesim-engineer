#include "core/style/FullHD1080p.h"

#include "core/style/1080p/Loading.h"
#include "core/style/1080p/RaceStanding.h"




UserInterface::Style::FullHD1080p::FullHD1080p() :
    m_loadingStyle(new UserInterface::Style::r1080p::Loading),
    m_raceStandingStyle(new UserInterface::Style::r1080p::RaceStanding) {



}



UserInterface::Style::ILoading* UserInterface::Style::FullHD1080p::GetLoadingStyle() const {

    return m_loadingStyle;

}



UserInterface::Style::IRaceStanding* UserInterface::Style::FullHD1080p::GetRaceStandingStyle() const {

    return m_raceStandingStyle;

}