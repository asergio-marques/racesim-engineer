#include "multiplayer_session/penalty/PenaltyIcon.h"

UserInterface::Widget::PenaltyIcon::PenaltyIcon(QWidget* parent) : 
    UserInterface::Widget::Container(UserInterface::Widget::ID::PenaltyIcon),
    m_flagIcon(nullptr),
    m_textBackground(nullptr),
    m_text(nullptr),
    m_active(false),
    m_timePen(0),
    m_driveThroughs(0),
    m_stopGos(0) {

}



void UserInterface::Widget::PenaltyIcon::addTimePenalty(const int32_t change) {

}



void UserInterface::Widget::PenaltyIcon::addDriveThrough(const int32_t change) {

}



void UserInterface::Widget::PenaltyIcon::addStopGo(const int32_t change) {

}



void UserInterface::Widget::PenaltyIcon::checkDisplayStatus() {



}