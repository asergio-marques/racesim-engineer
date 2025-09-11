#include "multiplayer_session/IDriverEntry.h"

#include <QWidget>
#include "base/Container.h"
#include "data/internal/LapTime.h"
#include "data/internal/Participant.h"
#include "data/internal/Penalty.h"
#include "data/internal/Session.h"



UserInterface::Widget::IDriverEntry::IDriverEntry() :
    UserInterface::Widget::Container(UserInterface::Widget::ID::DriverEntry),
    m_allWidgets(),
    m_driverIndex(0),
    m_currentPosition(0),
    m_isPlayer(false) {

}



const uint8_t UserInterface::Widget::IDriverEntry::GetCurrentPosition() const {

    return m_currentPosition;

}