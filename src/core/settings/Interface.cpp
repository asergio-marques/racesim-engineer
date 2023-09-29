#include "settings/Interface.h"
#include <pugixml.hpp>
#include "settings/ISetting.h"



Settings::Interface* Settings::Interface::m_p = new Settings::Interface;



Settings::Interface* Settings::Interface::getInstance() {

    return m_p;

}



const bool Settings::Interface::Init() {

    // TODO read config.xml and store settings
    return true;

}



Settings::ISetting* Settings::Interface::getSetting(const Settings::Key key) {

    return nullptr;

}