#include "screens/Interface.h"

#include <QWidget>
#include "panels/Interface.h"
#include "settings/WindowNumber.h"




UserInterface::Screen::Interface::Interface(UserInterface::PacketHandler* handler, QWidget* parent) :
    QWidget(parent),
    m_handler(handler) {



}